import os
import re
import pandas as pd
import argparse
from openpyxl import load_workbook

def insert_blank_rows(df):
    new_rows = []
    prev_problem = None

    for _, row in df.iterrows():
        if prev_problem is not None and row["Problem"] != prev_problem:
            # thêm 1 dòng trống khi Problem đổi
            new_rows.append({"Problem": "", "Config": "", "Max width SAT": "", "Min width UNSAT": ""})
        new_rows.append(row.to_dict())
        prev_problem = row["Problem"]

    return pd.DataFrame(new_rows)

def parse_logs(log_base_dir, output_file):
    rows = []

    max_sat_re = re.compile(r"Max width SAT:\s*(\S+).")
    min_unsat_re = re.compile(r"Min width UNSAT:\s*(\S+).")

    for config in os.listdir(log_base_dir):
        config_path = os.path.join(log_base_dir, config)
        if not os.path.isdir(config_path):
            continue

        for fname in os.listdir(config_path):
            if not fname.endswith(".log"):
                continue
            problem = fname.replace(".log", "")
            fpath = os.path.join(config_path, fname)

            with open(fpath, "r", encoding="utf-8", errors="ignore") as f:
                content = f.read()

            max_sat_match = max_sat_re.search(content)
            max_sat = max_sat_match.group(1) if max_sat_match else "-"

            min_unsat_match = min_unsat_re.search(content)
            min_unsat = min_unsat_match.group(1) if min_unsat_match else "-"

            rows.append({
                "Problem": problem,
                "Config": config,
                "Max width SAT": max_sat,
                "Min width UNSAT": min_unsat
            })

    # Xuất ra Excel
    df = pd.DataFrame(rows)
    df = df.sort_values(by=["Problem", "Config"])
    df = insert_blank_rows(df)
    df.to_excel(output_file, index=False)
    
def auto_fit(output_file):
    wb = load_workbook(output_file)
    ws = wb.active

    for col in ws.columns:
        max_length = 0
        col_letter = col[0].column_letter
        for cell in col:
            try:
                if cell.value:
                    max_length = max(max_length, len(str(cell.value)))
            except:
                pass
        adjusted_width = max_length + 2
        ws.column_dimensions[col_letter].width = adjusted_width

    wb.save(output_file)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Extract SAT/UNSAT results from logs")
    parser.add_argument("--log_dir", required=True, help="Path to log base directory")
    parser.add_argument("--output", required=True, help="Path to output Excel file")

    args = parser.parse_args()
    parse_logs(args.log_dir, args.output)
    auto_fit(args.output)
