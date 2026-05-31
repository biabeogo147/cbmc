#!/usr/bin/env python3
"""Wrap benchmark ISR/task entry functions in CBMC atomic sections."""

from __future__ import annotations

import argparse
import re
from pathlib import Path


def find_matching_brace(text: str, open_brace: int) -> int:
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
    for line in body.splitlines():
        if line.strip():
            return re.match(r"\s*", line).group(0) or "  "
    return "  "


def guard_returns(body: str, indent: str) -> str:
    return_pattern = re.compile(r"\breturn\b[^;]*;")

    def replacement(match: re.Match[str]) -> str:
        prefix = body[max(0, match.start() - 64) : match.start()]
        if "__CPROVER_atomic_end();" in prefix:
            return match.group(0)
        return f"__CPROVER_atomic_end();\n{indent}{match.group(0)}"

    return return_pattern.sub(replacement, body)


def last_statement_is_return(body: str) -> bool:
    body_without_comments = re.sub(r"//.*?$|/\*.*?\*/", "", body, flags=re.S | re.M)
    return re.search(r"\breturn\b[^;]*;\s*$", body_without_comments) is not None


def wrap_function_body(body: str) -> str:
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
