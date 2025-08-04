import os
import re
import argparse
import pandas as pd
import numpy as np

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

    # 3. Detect "Kill lower pid ..." lines
    terminations = set(
        int(pid) for pid in re.findall(r"Kill (?:lower|higher) pid (\d+)", text)
    )

    # Add these as special results
    for pid in terminations:
        if pid not in results:
            results[pid] = "TERM"
        if pid not in durations:
            durations[pid] = np.nan  # NaN time

    # 4. Extract summary info
    def extract_value(pattern, value_type=str):
        match = re.search(pattern, text)
        if match:
            val = match.group(1)
            return value_type(val) if val != "-" else "N/A"
        return "N/A"

    summary = {
        "Max width SAT": extract_value(r"Max width SAT:\s+(\d+|-)", int),
        "Min width UNSAT": extract_value(r"Min width UNSAT:\s+(\d+|-)", int),
        "Total real time (s)": extract_value(r"Total real time:\s+(\d+)", lambda x: round(int(x)/1000, 3)),
        "Total memory consumed (MB)": extract_value(r"Total memory consumed:\s+([\d.]+)", float)
    }

    # 5. Combine data
    all_widths = sorted(set(durations.keys()) | set(results.keys()))
    data = []
    for w in all_widths:
        time_ms = durations.get(w, np.nan)
        data.append({
            "Width": w,
            "SAT/UNSAT": results.get(w, "N/A"),
            "Time (ms)": time_ms,
            "Time (s)" : time_ms / 1000.0 if pd.notna(time_ms) else np.nan
        })

    df = pd.DataFrame(data)
    df = df.fillna("-")

    return df, summary

def main():
    parser = argparse.ArgumentParser(description="Extract SAT/UNSAT and timing results to Excel.")
    parser.add_argument('--folder', required=True, help='Path to folder containing .log files')
    parser.add_argument('--output', default='results.xlsx', help='Output Excel file name')
    args = parser.parse_args()

    folder_path = args.folder
    output_file = args.output

    with pd.ExcelWriter(output_file, engine="xlsxwriter") as writer:
        for filename in sorted(os.listdir(folder_path)):
            if not filename.endswith(".log"):
                continue

            filepath = os.path.join(folder_path, filename)
            df, summary = parse_file(filepath)

            sheet_name = os.path.splitext(filename)[0][:31]
            df.to_excel(writer, sheet_name=sheet_name, index=False, startrow=0, startcol=0)

            # Write summary to the right
            summary_items = list(summary.items())
            worksheet = writer.sheets[sheet_name]
            for i, (key, val) in enumerate(summary_items):
                worksheet.write(i, 5, key)
                worksheet.write(i, 6, val)

if __name__ == "__main__":
    main()
