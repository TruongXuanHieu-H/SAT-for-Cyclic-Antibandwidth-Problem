#!/bin/bash

TIME_LIMIT=1800
MEMORY_LIMIT=30000
SYMMETRY_BREAK="highest-degree"
WORKER_COUNT=8
LOG_DIR="logs/test_step"
ADD_CONFIGS="--step-from-lb"

mkdir -p "$LOG_DIR"

# ./build/cabw_enc datasets/harwell_boeing/A-pores_1.mtx.rnd   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/A-pores_1.log
# ./build/cabw_enc datasets/harwell_boeing/B-ibm32.mtx.rnd     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/B-ibm32.log
# ./build/cabw_enc datasets/harwell_boeing/C-bcspwr01.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/C-bcspwr01.log
# ./build/cabw_enc datasets/harwell_boeing/D-bcsstk01.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/D-bcsstk01.log
# ./build/cabw_enc datasets/harwell_boeing/E-bcspwr02.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/E-bcspwr02.log
# ./build/cabw_enc datasets/harwell_boeing/F-curtis54.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/F-curtis54.log
# ./build/cabw_enc datasets/harwell_boeing/G-will57.mtx.rnd    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/G-will57.log
# ./build/cabw_enc datasets/harwell_boeing/H-impcol_b.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/H-impcol_b.log
# ./build/cabw_enc datasets/harwell_boeing/I-ash85.mtx.rnd     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/I-ash85.log
# ./build/cabw_enc datasets/harwell_boeing/J-nos4.mtx.rnd      --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/J-nos4.log
# ./build/cabw_enc datasets/harwell_boeing/K-dwt__234.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/K-dwt__234.log
# ./build/cabw_enc datasets/harwell_boeing/L-bcspwr03.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/L-bcspwr03.log
# ./build/cabw_enc datasets/harwell_boeing/M-bcsstk06.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/M-bcsstk06.log
# ./build/cabw_enc datasets/harwell_boeing/N-bcsstk07.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/N-bcsstk07.log
# ./build/cabw_enc datasets/harwell_boeing/O-impcol_d.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/O-impcol_d.log
# ./build/cabw_enc datasets/harwell_boeing/P-can__445.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/P-can__445.log
# ./build/cabw_enc datasets/harwell_boeing/Q-494_bus.mtx.rnd   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/Q-494_bus.log
# ./build/cabw_enc datasets/harwell_boeing/R-dwt__503.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/R-dwt__503.log
./build/cabw_enc datasets/harwell_boeing/S-sherman4.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/S-sherman4.log
# ./build/cabw_enc datasets/harwell_boeing/T-dwt__592.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/T-dwt__592.log
# ./build/cabw_enc datasets/harwell_boeing/U-662_bus.mtx.rnd   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/U-662_bus.log
# ./build/cabw_enc datasets/harwell_boeing/V-nos6.mtx.rnd      --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/V-nos6.log
# ./build/cabw_enc datasets/harwell_boeing/W-685_bus.mtx.rnd   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/W-685_bus.log
# ./build/cabw_enc datasets/harwell_boeing/X-can__715.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/X-can__715.log
