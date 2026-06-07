#!/usr/bin/env python3
"""Scan imported corpora and rank likely interrupt/concurrency benchmark files.

Inputs:
  - --repo-root: repository root, default current directory.
  - Imported i-CBMC and IntAbs upstream source trees under check-src/benchmark-sources.

Output:
  - CSV candidate table at check-src/benchmarks/results/audit/candidate-scan.csv by default.

The score is only a triage heuristic. It favors larger files with main(),
CPROVER async labels, pthread_create, verifier thread metadata, and assertions.
It does not prove that a candidate is runnable without normalization.
"""

import argparse
import csv
import re
from dataclasses import dataclass
from pathlib import Path


SOURCE_SUFFIXES = {".c", ".i"}


@dataclass
class Candidate:
    name: str
    path: Path
    corpus: str
    loc: int
    async_labels: int
    pthread_create: int
    verifier_threads: int
    assertions: int
    main_functions: int
    case_family: str = "other"
    already_staged: bool = False
    recommended_phase: str = "backlog"

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


def slug(value: str) -> str:
    """Normalize a source-derived name into a benchmark case slug.

    Args:
        value: Raw file or directory name.

    Returns:
        Lowercase slug using hyphen separators.
    """
    value = value.replace("+", "-").replace("_", "-")
    value = re.sub(r"[^A-Za-z0-9-]+", "-", value)
    value = re.sub(r"-+", "-", value).strip("-")
    return value.lower()


def staged_case_names(repo: Path, corpus: str) -> set[str]:
    """Return existing normalized case directory names for one corpus.

    Args:
        repo: Repository root.
        corpus: Corpus folder name, for example icbmc or intabs.

    Returns:
        Set of normalized case names already present under cases/.
    """
    cases_dir = repo / "check-src" / "benchmark-sources" / corpus / "cases"
    if not cases_dir.exists():
        return set()
    return {path.name for path in cases_dir.iterdir() if path.is_dir()}


def case_family_for(path: Path) -> str:
    """Classify a candidate into a broad benchmark family.

    Args:
        path: Candidate path relative to the repository root.

    Returns:
        Family label used for intake planning.
    """
    text = path.as_posix().lower()
    if "rc-core" in text or "rc_core" in text or "rcmain" in text:
        return "rc-core"
    if "blink" in text:
        return "blink"
    if "logger2" in text or "logger1+2" in text or "logger" in text:
        return "logger"
    if "brake" in text:
        return "brake"
    if "wdt_pci" in text or "wdt-pci" in text:
        return "wdt-pci"
    if "sc520wdt" in text:
        return "sc520wdt"
    if "sc1200wdt" in text:
        return "sc1200wdt"
    if "i8xx_tco" in text or "i8xx-tco" in text:
        return "i8xx-tco"
    return "other"


def possible_case_names(path: Path, corpus: str) -> set[str]:
    """Infer likely normalized case names for one upstream source.

    Args:
        path: Candidate path relative to the repository root.
        corpus: Corpus name, for example icbmc or intabs.

    Returns:
        Set of names that may correspond to an existing normalized case.
    """
    names = {slug(path.stem), slug(path.parent.name)}
    parts = [part.lower() for part in path.parts]
    stem = path.stem.lower()
    parent = path.parent.name.lower()

    if corpus == "intabs":
        base = slug(parent)
        if "src" in parts and "test" in parts:
            names.add(f"{base}-src")
        names.add(base)
        if stem == "main2":
            names.add(f"{base}-main2")
            if "src" in parts and "test" in parts:
                names.add(f"{base}-src-main2")
    elif corpus == "icbmc":
        mapped = slug(stem)
        mapped = mapped.replace("-core", "-core").replace("rc-core", "rc-core")
        mapped = mapped.replace("rc-core-bug", "rc-core-bug")
        if mapped.endswith("-por-seq"):
            names.add(f"{mapped.removesuffix('-por-seq')}-seq")
        if mapped == "rc-core":
            names.add("rc-core")
        if mapped == "rc-core-bug":
            names.add("rc-core-bug")
        if mapped == "blink":
            names.add("blink")
        if mapped == "blink-bug":
            names.add("blink-bug")
        if mapped == "logger":
            names.add("logger")
        if mapped == "logger-bug":
            names.add("logger-bug")
        names.add(mapped)
    return {name for name in names if name}


def phase_for(path: Path, corpus: str, family: str, already_staged: bool) -> str:
    """Choose the intended intake phase for one candidate.

    Args:
        path: Candidate path relative to the repository root.
        corpus: Corpus name.
        family: Family label from case_family_for().
        already_staged: Whether this source already has a normalized case.

    Returns:
        Phase label used in the candidate scan CSV.
    """
    if already_staged:
        return "staged"
    text = path.as_posix().lower()
    if corpus == "intabs":
        if family in {"wdt-pci", "sc1200wdt", "i8xx-tco"} and "main2.c" not in text:
            return "phase-1"
        if "main2.c" in text or family == "rc-core":
            return "phase-4"
        return "backlog"
    if corpus == "icbmc":
        if family in {"rc-core", "blink"} and ("conc-code" in text or "seq-code" in text):
            return "phase-2"
        if family in {"logger", "brake"}:
            return "phase-3"
        return "backlog"
    return "backlog"


def inspect_file(path: Path, repo: Path, corpus: str, staged_names: set[str]):
    """Count concurrency/assertion markers for one source file.

    Args:
        path: Source file to inspect.
        repo: Repository root used to store a relative path in the result.
        corpus: Corpus name used for staged-case lookup.
        staged_names: Existing normalized case names for this corpus.

    Returns:
        Candidate metadata with LOC and marker counts.
    """
    text = path.read_text(errors="ignore")
    loc = len(text.splitlines())
    rel_path = path.relative_to(repo)
    inferred_names = possible_case_names(rel_path, corpus)
    already_staged = bool(inferred_names & staged_names)
    family = case_family_for(rel_path)
    return Candidate(
        name=path.with_suffix("").name,
        path=rel_path,
        corpus=corpus,
        loc=loc,
        async_labels=len(re.findall(r"__CPROVER_ASYNC_", text)),
        pthread_create=len(re.findall(r"\bpthread_create\s*\(", text)),
        verifier_threads=len(re.findall(r"__VERIFIER_threads|__CPROVER_threads", text)),
        assertions=len(re.findall(r"\bassert\s*\(", text)),
        main_functions=len(re.findall(r"\bmain\s*\(", text)),
        case_family=family,
        already_staged=already_staged,
        recommended_phase=phase_for(rel_path, corpus, family, already_staged),
    )


def scan(root: Path, repo: Path, corpus: str):
    """Return ranked candidate files from one corpus root.

    Args:
        root: Corpus directory to scan recursively.
        repo: Repository root used for relative paths.
        corpus: Corpus name used for staged-case lookup.

    Returns:
        Candidate list sorted by descending heuristic score.
    """
    candidates = []
    staged_names = staged_case_names(repo, corpus)
    for path in root.rglob("*"):
        if not path.is_file() or path.suffix not in SOURCE_SUFFIXES:
            continue
        item = inspect_file(path, repo, corpus, staged_names)
        if item.main_functions and (
            item.async_labels or item.pthread_create or item.verifier_threads or item.assertions
        ):
            candidates.append(item)
    return sorted(candidates, key=lambda item: item.score, reverse=True)


def main(argv=None):
    """CLI entry point that writes the candidate CSV report.

    Args:
        argv: Optional command-line argument list. When None, argparse reads
            from sys.argv.

    Returns:
        Process-style exit code. Returns 0 on success.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo-root", default=".")
    parser.add_argument("--limit", type=int, default=30)
    parser.add_argument("--csv-out", default="check-src/benchmarks/results/audit/candidate-scan.csv")
    args = parser.parse_args(argv)

    repo = Path(args.repo_root).resolve()
    roots = [
        ("i-CBMC", "icbmc", repo / "check-src/benchmark-sources/icbmc/upstream/extracted"),
        ("IntAbs", "intabs", repo / "check-src/benchmark-sources/intabs/upstream/repository"),
    ]
    rows = []
    for label, corpus, root in roots:
        items = scan(root, repo, corpus)[: args.limit]
        for item in items:
            rows.append(
                {
                    "corpus_label": label,
                    "corpus": corpus,
                    "path": item.path.as_posix(),
                    "family": item.case_family,
                    "staged": "yes" if item.already_staged else "no",
                    "phase": item.recommended_phase,
                    "loc": item.loc,
                    "async_labels": item.async_labels,
                    "pthread_create": item.pthread_create,
                    "thread_metadata": item.verifier_threads,
                    "assertions": item.assertions,
                    "score": item.score,
                }
            )
    out = Path(args.csv_out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", newline="", encoding="utf-8") as csv_file:
        fieldnames = [
            "corpus_label",
            "corpus",
            "path",
            "family",
            "staged",
            "phase",
            "loc",
            "async_labels",
            "pthread_create",
            "thread_metadata",
            "assertions",
            "score",
        ]
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)
    print(f"candidate scan: {out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
