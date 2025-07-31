import os
import re
import argparse
import pandas as pd

def parse_file(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        text = f.read()

    # 1. Extract solving durations
    durations = {
        int(w): int(t)
        for w, t in re.findall(r"\[w = (\d+)] .*?Solving duration: (\d+) ms", text)
    }

    # 2. Extract SAT/UNSAT results
    results = {
        int(w): status
        for w, status in re.findall(r"s \[w = (\d+)] (SAT|UNSAT)", text)
    }

    # 3. Combine both into a list of dicts
    all_widths = sorted(set(durations.keys()) | set(results.keys()))
    rows = []
    for w in all_widths:
        time_ms = durations.get(w, "N/A")
        rows.append({
            "Width": w,
            "SAT/UNSAT": results.get(w, "N/A"),
            "Time (ms)": time_ms,
            "Time (s)" : time_ms / 1000.0 if time_ms != "N/A" else "N/A"
        })

    return pd.DataFrame(rows)

def main():
    parser = argparse.ArgumentParser(description="Extract SAT/UNSAT and timing results to Excel.")
    parser.add_argument('--folder', required=True, help='Path to folder containing .log files')
    parser.add_argument('--output', default='results.xlsx', help='Output Excel file name')
    args = parser.parse_args()

    folder_path = args.folder
    output_file = args.output

    excel_writer = pd.ExcelWriter(output_file, engine="xlsxwriter")

    for filename in sorted(os.listdir(folder_path)):
        if filename.endswith(".log"):
            filepath = os.path.join(folder_path, filename)
            df = parse_file(filepath)
            sheet_name = os.path.splitext(filename)[0][:31]
            df.to_excel(excel_writer, sheet_name=sheet_name, index=False)

    excel_writer.close()

if __name__ == "__main__":
    main()
