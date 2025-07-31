import os
import re
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
        rows.append({
            "Width": w,
            "SAT/UNSAT": results.get(w, "N/A"),
            "Time (ms)": durations.get(w, -1)
        })

    return pd.DataFrame(rows)


folder_path = '../logs/harwell_boeing_no_symmetry_breaking'

excel_writer = pd.ExcelWriter("results.xlsx", engine="xlsxwriter")

for filename in sorted(os.listdir(folder_path)):
    if filename.endswith(".log"):
        filepath = os.path.join(folder_path, filename)
        df = parse_file(filepath)
        sheet_name = os.path.splitext(filename)[0][:31]  # Excel sheet name max 31 chars
        df.to_excel(excel_writer, sheet_name=sheet_name, index=False)

excel_writer.close()
