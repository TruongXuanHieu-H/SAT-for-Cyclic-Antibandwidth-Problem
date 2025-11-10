#!/bin/bash
# Script này chạy một danh sách cụ thể các file .sh

# Dừng nếu có lỗi ở bất kỳ script nào (tuỳ chọn, bỏ nếu muốn chạy hết)
# set -e  

# Danh sách các file .sh cần chạy
SCRIPTS=(
    "/home/truongxuanhieu/SAT-for-Cyclic-Antibandwidth-Problem/auto_run_sh/caterpillar/150s/run_all.sh"
    "/home/truongxuanhieu/SAT-for-Cyclic-Antibandwidth-Problem/auto_run_sh/cbt/150s/run_all.sh"
    "/home/truongxuanhieu/SAT-for-Cyclic-Antibandwidth-Problem/auto_run_sh/double_star/150s/run_all.sh"
    "/home/truongxuanhieu/SAT-for-Cyclic-Antibandwidth-Problem/auto_run_sh/hypercube/150s/run_all.sh"
    "/home/truongxuanhieu/SAT-for-Cyclic-Antibandwidth-Problem/auto_run_sh/rand_gen_graph_2013/150s/run_all.sh"
)

echo "=== Bắt đầu chạy các script được chọn ==="
echo

for script in "${SCRIPTS[@]}"; do
    if [ -f "$script" ]; then
        echo ">>> Đang chạy: $script"
        chmod +x "$script"
        bash "$script"
        status=$?
        if [ $status -eq 0 ]; then
            echo "✅ Thành công: $script"
        else
            echo "❌ Lỗi ($status): $script"
        fi
    else
        echo "⚠️ Không tìm thấy file: $script"
    fi
    echo "-----------------------------"
done

echo
echo "=== Hoàn tất ==="