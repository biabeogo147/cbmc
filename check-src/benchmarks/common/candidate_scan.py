#!/usr/bin/env python3
"""Scan imported corpora and rank likely interrupt/concurrency benchmark files.

Inputs:
  - --repo-root: repository root, default current directory.
  - Imported i-CBMC and IntAbs upstream source trees under check-src/benchmark-sources.

Output:
  - Markdown candidate table at check-src/benchmark-sources/CANDIDATES.md by default.

The score is only a triage heuristic. It favors larger files with main(),
CPROVER async labels, pthread_create, verifier thread metadata, and assertions.
It does not prove that a candidate is runnable without normalization.
"""

import argparse
import re
from dataclasses import dataclass
from pathlib import Path


SOURCE_SUFFIXES = {".c", ".i"}


@dataclass
class Candidate:
    name: str
    path: Path
    loc: int
    async_labels: int
    pthread_create: int
    verifier_threads: int
    assertions: int
    main_functions: int

    @property
    def score(self):
        """Compute the heuristic ranking score.

        Args:
            None.

        Returns:
            Numeric score used to sort candidate files descending.
        """
        return (
            self.loc
            + self.async_labels * 500
            + self.pthread_create * 500
            + self.verifier_threads * 500
            + self.assertions * 50
        )


def inspect_file(path: Path, repo: Path):
    """Count concurrency/assertion markers for one source file.

    Args:
        path: Source file to inspect.
        repo: Repository root used to store a relative path in the result.

    Returns:
        Candidate metadata with LOC and marker counts.
    """
    text = path.read_text(errors="ignore")
    loc = len(text.splitlines())
    return Candidate(
        name=path.with_suffix("").name,
        path=path.relative_to(repo),
        loc=loc,
        async_labels=len(re.findall(r"__CPROVER_ASYNC_", text)),
        pthread_create=len(re.findall(r"\bpthread_create\s*\(", text)),
        verifier_threads=len(re.findall(r"__VERIFIER_threads|__CPROVER_threads", text)),
        assertions=len(re.findall(r"\bassert\s*\(", text)),
        main_functions=len(re.findall(r"\bmain\s*\(", text)),
    )


def scan(root: Path, repo: Path):
    """Return ranked candidate files from one corpus root.

    Args:
        root: Corpus directory to scan recursively.
        repo: Repository root used for relative paths.

    Returns:
        Candidate list sorted by descending heuristic score.
    """
    candidates = []
    for path in root.rglob("*"):
        if not path.is_file() or path.suffix not in SOURCE_SUFFIXES:
            continue
        item = inspect_file(path, repo)
        if item.main_functions and (
            item.async_labels or item.pthread_create or item.verifier_threads or item.assertions
        ):
            candidates.append(item)
    return sorted(candidates, key=lambda item: item.score, reverse=True)


def main(argv=None):
    """CLI entry point that writes the candidate Markdown report.

    Args:
        argv: Optional command-line argument list. When None, argparse reads
            from sys.argv.

    Returns:
        Process-style exit code. Returns 0 on success.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo-root", default=".")
    parser.add_argument("--limit", type=int, default=30)
    parser.add_argument("--md-out", default="check-src/benchmark-sources/CANDIDATES.md")
    args = parser.parse_args(argv)

    repo = Path(args.repo_root).resolve()
    roots = [
        ("i-CBMC", repo / "check-src/benchmark-sources/icbmc/upstream/extracted"),
        ("IntAbs", repo / "check-src/benchmark-sources/intabs/upstream/repository"),
    ]
    lines = ["# Benchmark Candidate Scan", ""]
    for label, root in roots:
        items = scan(root, repo)[: args.limit]
        lines += [
            f"## {label}",
            "",
            "| Path | LOC | async labels | pthread_create | thread metadata | assert | score |",
            "| --- | ---: | ---: | ---: | ---: | ---: | ---: |",
        ]
        for item in items:
            lines.append(
                f"| `{item.path.as_posix()}` | {item.loc} | {item.async_labels} | "
                f"{item.pthread_create} | {item.verifier_threads} | {item.assertions} | {item.score} |"
            )
        lines.append("")
    Path(args.md_out).write_text("\n".join(lines), encoding="utf-8")
    print(f"candidate report: {args.md_out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
