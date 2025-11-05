#!/bin/bash

TIME_LIMIT=1800
MEMORY_LIMIT=30000
SYMMETRY_BREAK="highest-degree"
WORKER_COUNT=8
ENC_DIR="../../../build"
DATASET_DIR="../../../datasets/unknow_optimal/complete_binary_trees"
LOG_DIR="../../../logs_1800s/unknow_optimal/complete_binary_trees/binarysearchfromLB_highestdegree_8workers"
ADD_CONFIGS="--binary-search-from-lb"

mkdir -p "$LOG_DIR" 

$ENC_DIR/cabw_enc $DATASET_DIR/cbt_30.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_30.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_31.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_31.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_32.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_32.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_33.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_33.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_34.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_34.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_35.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_35.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_45.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_45.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_46.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_46.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_47.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_47.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_48.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_48.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_49.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_49.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_50.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_50.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_500.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_500.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_510.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_510.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_550.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_550.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_600.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_600.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_620.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_620.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_630.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_630.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_640.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_640.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_730.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_730.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_790.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_790.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_880.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_880.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_910.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_910.log
$ENC_DIR/cabw_enc $DATASET_DIR/cbt_950.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/cbt_950.log

