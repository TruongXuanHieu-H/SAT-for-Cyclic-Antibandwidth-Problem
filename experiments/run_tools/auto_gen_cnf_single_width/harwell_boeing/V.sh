#!/bin/bash

INSTANCE_NAME="V-nos6"
SYMMETRY_BREAK="highest-degree"
WORKER_COUNT=1
ENC_DIR="../../build"
DATASET_DIR="../../datasets/unknow_optimal/harwell_boeing"
DIMAC_DIR="../../logs_dimacs_single_width/harwell_boeing"
LB_CONFIG=272
UB_CONFIG=336

mkdir -p "$DIMAC_DIR"

echo "Running experiments for $INSTANCE_NAME with width w from $LB_CONFIG to $UB_CONFIG"
for ((w=LB_CONFIG; w<=UB_CONFIG; w++)); do
    echo "Running w = $w ..."
    
    $ENC_DIR/cabw_enc $DATASET_DIR/$INSTANCE_NAME.mtx.rnd \
        --ladder \
        -symmetry-break $SYMMETRY_BREAK \
        -worker-count $WORKER_COUNT \
        -set-lb $w \
        -set-ub $w \
        -just-print-dimacs $DIMAC_DIR

done