"""Read-only manufacturing checks. Run from any directory; Python 3 standard library only."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import posixpath
import re
import sys
from pathlib import Path
from urllib.parse import unquote, urlsplit
from xml.etree import ElementTree as ET
from zipfile import ZipFile


ROOT = Path(__file__).resolve().parents[2]
MECHANICAL = ROOT / "hardware/mechanical"
NS = {"s": "http://schemas.openxmlformats.org/spreadsheetml/2006/main"}
REL_NS = "http://schemas.openxmlformats.org/officeDocument/2006/relationships"
DOCS = (
    "hardware/mechanical/README.md",
    "hardware/mechanical/README.zh-CN.md",
    "hardware/mechanical/manufacturing-release.zh-CN.md",
    "hardware/mechanical/build-record.zh-CN.md",
    "docs/build/01-overview.zh-CN.md",
    "docs/build/02-frame.zh-CN.md",
    "docs/build/08-enclosure-assembly.zh-CN.md",
    "docs/build/09-sealing-trim.zh-CN.md",
)


def fingerprint(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def workbook_rows(path: Path, sheet_name: str) -> list[list[str]]:
    """Decode stored cells without rewriting the workbook or recalculating formulas."""
    with ZipFile(path) as book:
        strings = []
        if "xl/sharedStrings.xml" in book.namelist():
            strings = [
                "".join(node.itertext())
                for node in ET.fromstring(book.read("xl/sharedStrings.xml"))
            ]
        sheets = ET.fromstring(book.read("xl/workbook.xml")).find("s:sheets", NS)
        sheet = next(item for item in sheets if item.get("name") == sheet_name)
        rel_id = sheet.get(f"{{{REL_NS}}}id")
        relations = ET.fromstring(book.read("xl/_rels/workbook.xml.rels"))
        target = next(item.get("Target") for item in relations if item.get("Id") == rel_id)
        member = target.lstrip("/") if target.startswith("/") else posixpath.normpath("xl/" + target)
        data = ET.fromstring(book.read(member))
        rows = []
        for row in data.findall("s:sheetData/s:row", NS):
            cells = {}
            for cell in row:
                letters = re.match(r"[A-Z]+", cell.get("r", "")).group()
                column = 0
                for letter in letters:
                    column = column * 26 + ord(letter) - ord("A") + 1
                if cell.find("s:f", NS) is not None:
                    raise ValueError(f"{sheet_name}!{cell.get('r')}: unexpected formula in BOM table")
                kind = cell.get("t")
                value = cell.findtext("s:v", default="", namespaces=NS)
                if kind == "s":
                    value = strings[int(value)]
                elif kind == "inlineStr":
                    value = "".join(cell.find("s:is", NS).itertext())
                cells[column - 1] = value
            rows.append([cells.get(i, "") for i in range(max(cells, default=-1) + 1)])
        return rows


def run(original_models: Path | None = None) -> dict:
    errors = []
    manifest = json.loads((MECHANICAL / "manifest.json").read_text(encoding="utf-8-sig"))
    for archive in manifest["archives"]:
        data = (MECHANICAL / archive["path"]).read_bytes()
        if len(data) != archive["bytes"] or fingerprint(data) != archive["sha256"]:
            errors.append(f"archive checksum: {archive['path']}")
    for item in manifest["files"]:
        published = MECHANICAL / item["published_path"]
        if "archive_member" in item:
            with ZipFile(published) as archive:
                data = archive.read(item["archive_member"])
        else:
            data = published.read_bytes()
        if len(data) != item["bytes"] or fingerprint(data) != item["sha256"]:
            errors.append(f"published checksum: {item['source_relative_path']}")
        if original_models is not None:
            source = original_models / item["source_relative_path"]
            if not source.is_file() or fingerprint(source.read_bytes()) != item["sha256"]:
                errors.append(f"original checksum: {item['source_relative_path']}")
    counts = {}
    for stem, sheet in (("BOM", "本体 BOM"), ("BOM-electronics", "舱内 BOM")):
        with (ROOT / f"hardware/bom/{stem}.csv").open(encoding="utf-8-sig", newline="") as handle:
            csv_rows = list(csv.reader(handle))
        width = len(csv_rows[0])
        table = csv_rows[1:]
        ids = [row[0] for row in table]
        if len(ids) != len(set(ids)):
            errors.append(f"{stem}: duplicate CSV IDs")
        book_rows = workbook_rows(ROOT / f"hardware/bom/{stem}.xlsx", sheet)
        start = next(i for i, row in enumerate(book_rows) if row and row[0] == ids[0])
        actual = [row[:width] + [""] * max(0, width - len(row)) for row in book_rows[start:]]
        # Ignore only fully empty trailing rows, never missing quantities or extra items.
        while actual and not any(actual[-1]):
            actual.pop()
        if len(table) != len(actual):
            errors.append(f"{stem}: CSV rows {len(table)} != XLSX rows {len(actual)}")
        for expected, received in zip(table, actual):
            for column, (left, right) in enumerate(zip(expected, received), 1):
                if left != right:
                    errors.append(f"{stem}/{expected[0]} column {column}: CSV/XLSX mismatch")
        counts[stem] = len(table)
    checked_links = 0
    for relative in DOCS:
        doc = ROOT / relative
        for target in re.findall(r"\]\(([^)]+)\)", doc.read_text(encoding="utf-8-sig")):
            target = target.strip("<>")
            parsed = urlsplit(target)
            if parsed.scheme or not parsed.path:
                continue
            checked_links += 1
            if not (doc.parent / unquote(parsed.path)).exists():
                errors.append(f"missing local link in {relative}: {target}")
    return {
        "published_source_files": len(manifest["files"]),
        "archives": len(manifest["archives"]),
        "original_models_checked": original_models is not None,
        "bom_data_rows": counts,
        "local_link_targets_checked": checked_links,
        "errors": errors,
        "limitations": "No geometry, external URL, Markdown anchor, visual, manufacturing or hardware validation.",
    }


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original-models", type=Path, help="Optional source model directory to compare read-only")
    args = parser.parse_args()
    try:
        result = run(args.original_models)
    except (OSError, ValueError, KeyError, StopIteration, ET.ParseError) as exc:
        print(f"Check could not finish: {exc}", file=sys.stderr)
        sys.exit(1)
    print(json.dumps(result, ensure_ascii=False, indent=2))
    sys.exit(1 if result["errors"] else 0)
