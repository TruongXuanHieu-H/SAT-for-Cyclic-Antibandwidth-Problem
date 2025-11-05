#!/bin/bash

TIME_LIMIT=150
MEMORY_LIMIT=30000
SYMMETRY_BREAK="highest-degree"
WORKER_COUNT=4
ENC_DIR="../../../build"
DATASET_DIR="../../../datasets/conjecture_optimal/double_star"
LOG_DIR="../../../logs_150s/conjecture_optimal/double_star/binarysearchbfs_highestdegree_4workers"
ADD_CONFIGS="--binary-search-bfs"

mkdir -p "$LOG_DIR"

$ENC_DIR/cabw_enc $DATASET_DIR/double_star_15_5.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_15_5.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_15_7.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_15_7.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_15_10.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_15_10.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_15_12.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_15_12.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_30_20.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_30_20.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_30_25.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_30_25.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_35_20.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_35_20.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_35_25.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_35_25.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_40_20.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_40_20.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_40_25.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_40_25.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_40_30.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_40_30.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_50_20.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_50_20.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_50_25.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_50_25.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_50_30.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_50_30.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_100_20.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_100_20.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_100_25.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_100_25.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_100_30.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_100_30.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_150_20.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_150_20.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_150_25.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_150_25.log
$ENC_DIR/cabw_enc $DATASET_DIR/double_star_150_30.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/double_star_150_30.log
