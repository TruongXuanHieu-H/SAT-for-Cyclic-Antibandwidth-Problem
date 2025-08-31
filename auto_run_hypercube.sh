#!/bin/bash

TIME_LIMIT=1800
MEMORY_LIMIT=30000
SYMMETRY_BREAK="highest-degree"
WORKER_COUNT=8
DATASET_DIR="datasets/conjecture_optimal/hypercube"
LOG_DIR="logs/conjecture_optimal/hypercube/binarysearchbfs_highestdegree_8workers"
ADD_CONFIGS="--binary-search-bfs"

mkdir -p "$LOG_DIR"

./build/cabw_enc $DATASET_DIR/hypercube_4_16.txt      --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/hypercube_4_16.log
./build/cabw_enc $DATASET_DIR/hypercube_5_32.txt      --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/hypercube_5_32.log
./build/cabw_enc $DATASET_DIR/hypercube_6_64.txt      --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/hypercube_6_64.log
./build/cabw_enc $DATASET_DIR/hypercube_7_128.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/hypercube_7_128.log
./build/cabw_enc $DATASET_DIR/hypercube_8_256.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/hypercube_8_256.log
./build/cabw_enc $DATASET_DIR/hypercube_9_512.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/hypercube_9_512.log
./build/cabw_enc $DATASET_DIR/hypercube_10_1024.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/hypercube_10_1024.log
