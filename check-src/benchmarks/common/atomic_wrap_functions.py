#!/usr/bin/env python3
"""Wrap benchmark ISR/task entry functions in CBMC atomic sections.

Inputs:
  - source: one C source file to edit in place.
  - functions: one or more function names that should be atomic.

Output:
  - The same source file, rewritten with __CPROVER_atomic_begin/end around
    matching function bodies. The script prints how many functions it changed.

Notes:
  - This is a normalization helper for benchmark sources, not part of the
    benchmark runner's timed phases.
  - It does not define fallback macros for CBMC atomic builtins; the benchmark
    should keep the real CBMC semantics.
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path


def find_matching_brace(text: str, open_brace: int) -> int:
    """Return the closing brace offset while skipping comments and strings.

    Args:
        text: Full source text.
        open_brace: Offset of the opening brace to match.

    Returns:
        Offset of the matching closing brace.
    """
    depth = 0
    i = open_brace
    state = "code"
    while i < len(text):
        ch = text[i]
        nxt = text[i + 1] if i + 1 < len(text) else ""

        if state == "code":
            if ch == "/" and nxt == "/":
                state = "line_comment"
                i += 2
                continue
            if ch == "/" and nxt == "*":
                state = "block_comment"
                i += 2
                continue
            if ch == '"':
                state = "string"
                i += 1
                continue
            if ch == "'":
                state = "char"
                i += 1
                continue
            if ch == "{":
                depth += 1
            elif ch == "}":
                depth -= 1
                if depth == 0:
                    return i
        elif state == "line_comment":
            if ch == "\n":
                state = "code"
        elif state == "block_comment":
            if ch == "*" and nxt == "/":
                state = "code"
                i += 2
                continue
        elif state == "string":
            if ch == "\\":
                i += 2
                continue
            if ch == '"':
                state = "code"
        elif state == "char":
            if ch == "\\":
                i += 2
                continue
            if ch == "'":
                state = "code"
        i += 1
    raise ValueError(f"unmatched brace at offset {open_brace}")


def function_matches(text: str, function_name: str) -> list[tuple[int, int, int]]:
    """Find function definitions and their body brace ranges.

    Args:
        text: Full source text.
        function_name: Function name to locate.

    Returns:
        List of tuples containing match start, opening brace offset, and closing
        brace offset.
    """
    pattern = re.compile(
        rf"(?m)(^|\n)([A-Za-z_][\w\s\*\(\),\[\]]*?\b"
        rf"{re.escape(function_name)}\s*\([^;{{}}]*\)\s*)\{{"
    )
    matches: list[tuple[int, int, int]] = []
    for match in pattern.finditer(text):
        open_brace = match.end() - 1
        close_brace = find_matching_brace(text, open_brace)
        matches.append((match.start(), open_brace, close_brace))
    return matches


def indent_for_body(body: str) -> str:
    """Infer indentation for inserted atomic statements.

    Args:
        body: Function body text between braces.

    Returns:
        Leading whitespace from the first non-empty body line, or two spaces.
    """
    for line in body.splitlines():
        if line.strip():
            return re.match(r"\s*", line).group(0) or "  "
    return "  "


def guard_returns(body: str, indent: str) -> str:
    """Insert atomic_end before return statements so early returns are guarded.

    Args:
        body: Function body text.
        indent: Indentation to use for rewritten return lines.

    Returns:
        Function body text with atomic_end inserted before return statements.
    """
    return_pattern = re.compile(r"\breturn\b[^;]*;")

    def replacement(match: re.Match[str]) -> str:
        """Rewrite one return statement match.

        Args:
            match: Regex match for a return statement.

        Returns:
            Original return statement or atomic_end plus the return statement.
        """
        prefix = body[max(0, match.start() - 64) : match.start()]
        if "__CPROVER_atomic_end();" in prefix:
            return match.group(0)
        return f"__CPROVER_atomic_end();\n{indent}{match.group(0)}"

    return return_pattern.sub(replacement, body)


def last_statement_is_return(body: str) -> bool:
    """Check whether a body already ends with a return statement.

    Args:
        body: Function body text.

    Returns:
        True when the final non-comment statement is return; otherwise False.
    """
    body_without_comments = re.sub(r"//.*?$|/\*.*?\*/", "", body, flags=re.S | re.M)
    return re.search(r"\breturn\b[^;]*;\s*$", body_without_comments) is not None


def wrap_function_body(body: str) -> str:
    """Return an atomic-wrapped body, or the original body if already wrapped.

    Args:
        body: Function body text between braces.

    Returns:
        Rewritten body with atomic begin/end calls, or unchanged body when it
        already contains __CPROVER_atomic_begin.
    """
    if "__CPROVER_atomic_begin" in body:
        return body

    indent = indent_for_body(body)
    guarded = guard_returns(body, indent)
    wrapped = f"\n{indent}__CPROVER_atomic_begin();"
    if guarded.startswith("\n"):
        wrapped += guarded
    else:
        wrapped += "\n" + guarded

    if not last_statement_is_return(guarded):
        trailing = indent if wrapped.endswith("\n") else "\n" + indent
        wrapped += f"{trailing}__CPROVER_atomic_end();\n"
    return wrapped


def wrap_functions(text: str, function_names: list[str]) -> tuple[str, int]:
    """Wrap all requested functions and return updated text plus change count.

    Args:
        text: Full source text.
        function_names: Function names to wrap.

    Returns:
        Tuple of updated source text and number of function bodies changed.
    """
    replacements: list[tuple[int, int, str]] = []
    for function_name in function_names:
        for _, open_brace, close_brace in function_matches(text, function_name):
            body = text[open_brace + 1 : close_brace]
            wrapped = wrap_function_body(body)
            if wrapped != body:
                replacements.append((open_brace + 1, close_brace, wrapped))

    for start, end, replacement in sorted(replacements, reverse=True):
        text = text[:start] + replacement + text[end:]
    return text, len(replacements)


def main() -> int:
    """CLI entry point for atomic wrapping.

    Args:
        None. Reads command-line arguments with argparse.

    Returns:
        Process-style exit code. Returns 0 on success.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("source", type=Path)
    parser.add_argument("functions", nargs="+")
    args = parser.parse_args()

    text = args.source.read_text()
    updated, wrapped_count = wrap_functions(text, args.functions)
    if wrapped_count:
        args.source.write_text(updated)
    print(f"{args.source}: wrapped {wrapped_count} function(s)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
