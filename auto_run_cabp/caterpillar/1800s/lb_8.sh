#!/bin/bash

TIME_LIMIT=1800
MEMORY_LIMIT=30000
SYMMETRY_BREAK="highest-degree"
WORKER_COUNT=8
ENC_DIR="../../../build"
DATASET_DIR="../../../datasets/unknow_optimal/caterpillar"
LOG_DIR="../../../logs_1800s/unknow_optimal/caterpillar/binarysearchfromLB_highestdegree_8workers"
ADD_CONFIGS="--binary-search-from-lb"

mkdir -p "$LOG_DIR"

$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_5_4.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_5_4.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_5_5.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_5_5.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_5_6.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_5_6.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_5_7.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_5_7.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_9_4.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_9_4.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_9_5.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_9_5.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_9_6.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_9_6.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_9_7.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_9_7.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_10_4.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_10_4.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_10_5.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_10_5.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_10_6.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_10_6.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_10_7.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_10_7.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_15_4.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_15_4.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_15_5.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_15_5.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_15_6.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_15_6.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_15_7.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_15_7.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_20_4.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_20_4.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_20_5.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_20_5.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_20_6.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_20_6.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_20_7.txt  --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_20_7.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_20_10.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_20_10.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_20_15.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_20_15.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_20_20.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_20_20.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_20_25.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_20_25.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_25_10.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_25_10.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_25_15.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_25_15.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_25_20.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_25_20.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_25_25.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_25_25.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_30_10.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_30_10.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_30_15.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_30_15.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_30_20.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_30_20.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_30_25.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_30_25.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_35_10.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_35_10.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_35_15.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_35_15.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_35_20.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_35_20.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_35_25.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_35_25.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_40_10.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_40_10.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_40_15.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_40_15.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_40_20.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_40_20.log
$ENC_DIR/cabw_enc $DATASET_DIR/caterpillar_40_25.txt --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/caterpillar_40_25.log
