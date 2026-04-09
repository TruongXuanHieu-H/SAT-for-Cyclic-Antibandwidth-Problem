#!/bin/bash

INSTANCE_NAME="N-bcsstk07"
TIME_LIMIT=3600
MEMORY_LIMIT=30000
SYMMETRY_BREAK="highest-degree"
WORKER_COUNT=1
ENC_DIR="../../../../../build"
DATASET_DIR="../../../../../datasets/unknow_optimal/harwell_boeing"
LOG_DIR="../../../../../experiments/results/logs_single_width/harwell_boeing"
LB_CONFIG=33
UB_CONFIG=42

mkdir -p "$LOG_DIR"

echo "Running experiments for $INSTANCE_NAME with width w from $LB_CONFIG to $UB_CONFIG"
for ((w=LB_CONFIG; w<=UB_CONFIG; w++)); do
    echo "Running w = $w ..."
    
    $ENC_DIR/cabw_enc $DATASET_DIR/$INSTANCE_NAME.mtx.rnd \
        --ladder \
        -limit-real-time $TIME_LIMIT \
        -limit-memory $MEMORY_LIMIT \
        -symmetry-break $SYMMETRY_BREAK \
        -worker-count $WORKER_COUNT \
        -set-lb $w \
        -set-ub $w \
        2>&1 | tee $LOG_DIR/$INSTANCE_NAME-$w.log

done