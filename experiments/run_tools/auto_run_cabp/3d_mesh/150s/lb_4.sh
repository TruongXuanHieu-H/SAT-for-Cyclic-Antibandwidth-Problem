#!/bin/bash

TIME_LIMIT=150
MEMORY_LIMIT=30000
SYMMETRY_BREAK="highest-degree"
WORKER_COUNT=4
ENC_DIR="../../../build"
DATASET_DIR="../../../datasets/conjecture_optimal/3dmesh"
LOG_DIR="../../../logs_150s/conjecture_optimal/3dmesh/binarysearchfromLB_highestdegree_4workers"
ADD_CONFIGS="--binary-search-from-lb"

mkdir -p "$LOG_DIR"

$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_2_2_3.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_2_2_3.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_2_2_168.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_2_2_168.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_2_2_335.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_2_2_335.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_2_2_500.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_2_2_500.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_3_3_3.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_3_3_3.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_3_3_135.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_3_3_135.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_3_3_270.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_3_3_270.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_3_3_400.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_3_3_400.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_4_4_5.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_4_4_5.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_4_4_68.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_4_4_68.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_4_4_137.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_4_4_137.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_4_4_200.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_4_4_200.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_5_5_7.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_5_5_7.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_5_5_35.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_5_5_35.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_5_5_70.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_5_5_70.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_5_5_100.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_5_5_100.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_6_6_8.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_6_6_8.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_6_6_36.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_6_6_36.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_6_6_72.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_6_6_72.log
$ENC_DIR/cabw_enc $DATASET_DIR/3dmesh_6_6_100.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_6_6_100.log

