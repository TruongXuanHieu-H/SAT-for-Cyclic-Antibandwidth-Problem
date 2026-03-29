import os
import re
from openpyxl import Workbook

LOG_DIR = "./harwell_boeing"
OUTPUT_FILE = "results.xlsx"

def parse_log(filepath):
    filename = os.path.basename(filepath)

    # Tên problem
    instance = re.sub(r'-\d+\.log$', '', filename)

    # Width
    width_match = re.search(r'-(\d+)\.log$', filename)
    width = width_match.group(1) if width_match else "-"

    max_sat = None
    min_unsat = None
    result = "-"
    time_ms = "-"
    memory_mb = "-"

    with open(filepath, 'r') as f:
        for line in f:
            if "Max width SAT:" in line:
                m = re.search(r'Max width SAT:\s+(\d+)', line)
                if m:
                    max_sat = m.group(1)

            if "Min width UNSAT:" in line:
                m = re.search(r'Min width UNSAT:\s+(\d+)', line)
                if m:
                    min_unsat = m.group(1)

            if "Total real time:" in line:
                m = re.search(r'Total real time:\s+(\d+)', line)
                if m:
                    time_ms = int(m.group(1))

            if "Total memory consumed:" in line:
                m = re.search(r'Total memory consumed:\s+([\d\.]+)', line)
                if m:
                    memory_mb = float(m.group(1))

    if max_sat == width:
        result = "SAT"
    elif min_unsat == width:
        result = "UNSAT"

    return [instance, int(width) if width.isdigit() else width, result, time_ms, memory_mb]


def main():
    rows = []
    for file in os.listdir(LOG_DIR):
        if file.endswith(".log"):
            filepath = os.path.join(LOG_DIR, file)
            rows.append(parse_log(filepath))

    # Sort theo instance + width
    rows.sort(key=lambda x: (x[0], x[1] if isinstance(x[1], int) else float('inf')))

    # Tạo Excel
    wb = Workbook()
    ws = wb.active
    ws.title = "Results"

    # Header
    ws.append(["Instance", "Width", "Result", "Time (ms)", "Memory (MB)"])

    # Data
    for row in rows:
        ws.append(row)

    # Auto width (optional)
    for col in ws.columns:
        max_length = max(len(str(cell.value)) if cell.value else 0 for cell in col)
        ws.column_dimensions[col[0].column_letter].width = max_length + 2

    wb.save(OUTPUT_FILE)
    print(f"Saved to {OUTPUT_FILE}")


if __name__ == "__main__":
    main()