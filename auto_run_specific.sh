#!/bin/bash

TIME_LIMIT=1800
MEMORY_LIMIT=30000
SYMMETRY_BREAK="highest-degree"
WORKER_COUNT=4
LOG_DIR="logs/harwell_boeing/test_width"
ADD_CONFIGS="--iterate-from-lb"

mkdir -p "$LOG_DIR"


./build/cabw_enc datasets/harwell_boeing/S-sherman4.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS -set-lb 254 -set-ub 254 2>&1 | tee $LOG_DIR/S-sherman4_254.log
./build/cabw_enc datasets/harwell_boeing/S-sherman4.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS -set-lb 256 -set-ub 256 2>&1 | tee $LOG_DIR/S-sherman4_256.log
./build/cabw_enc datasets/harwell_boeing/S-sherman4.mtx.rnd  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS -set-lb 258 -set-ub 258 2>&1 | tee $LOG_DIR/S-sherman4_258.log
./build/cabw_enc datasets/harwell_boeing/V-nos6.mtx.rnd      --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS -set-lb 325 -set-ub 325 2>&1 | tee $LOG_DIR/V-nos6_325.log
./build/cabw_enc datasets/harwell_boeing/V-nos6.mtx.rnd      --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS -set-lb 328 -set-ub 328 2>&1 | tee $LOG_DIR/V-nos6_328.log
