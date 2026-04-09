import os
import argparse
import subprocess

def main():
    parser = argparse.ArgumentParser(description="Extract SAT/UNSAT and timing results to Excel.")
    parser.add_argument('--folder', required=True, help='Path to folder')
    parser.add_argument('--output', default='results.xlsx', help='Output Excel file name')
    args = parser.parse_args()

    main_log_folder_path = args.folder
    main_export_folder_path = args.output

    level2_log_folders_absolute = []
    level2_log_folders_relative = []
    export_files = []

    for root, dirs, files in os.walk(main_log_folder_path):
        for d in dirs:
            absolute_path = os.path.join(root, d)
            relative_path = os.path.relpath(absolute_path, main_log_folder_path)  # đường dẫn tương đối
            # đếm số cấp
            depth = relative_path.count(os.sep) + 1
            if depth == 2:   # chỉ lấy folder bậc 2
                level2_log_folders_absolute.append(absolute_path)
                level2_log_folders_relative.append(relative_path)
                export_files.append(os.path.join(main_export_folder_path, relative_path + ".xlsx"))

    
    for f in export_files:
        os.makedirs(os.path.dirname(f), exist_ok=True) 
        
    
    for abs_path, exp_file in zip(level2_log_folders_absolute, export_files):
        cmd = [
            "python3", "export_summary_configs.py",
            "--folder", abs_path,
            "--output", exp_file
        ]
        print(">>> Running:", " ".join(cmd))
        subprocess.run(cmd, check=True)
    
if __name__ == "__main__":
    main()
