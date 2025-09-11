#!/bin/bash

TIME_LIMIT=1800
MEMORY_LIMIT=30000
SYMMETRY_BREAK="highest-degree"
WORKER_COUNT=8
INPUT_DIR="datasets/3dmesh"
LOG_DIR="logs_test/3dmesh/binarysearchbfs-highestdegree_8workers"
ADD_CONFIGS="--binary-search-bfs"

mkdir -p "$LOG_DIR"

./build/cabw_enc $INPUT_DIR/3dmesh_2_2_3.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_2_2_3.log
./build/cabw_enc $INPUT_DIR/3dmesh_2_2_168.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_2_2_168.log
./build/cabw_enc $INPUT_DIR/3dmesh_2_2_335.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_2_2_335.log
./build/cabw_enc $INPUT_DIR/3dmesh_2_2_500.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_2_2_500.log
./build/cabw_enc $INPUT_DIR/3dmesh_3_3_3.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_3_3_3.log
./build/cabw_enc $INPUT_DIR/3dmesh_3_3_135.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_3_3_135.log
./build/cabw_enc $INPUT_DIR/3dmesh_3_3_270.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_3_3_270.log
./build/cabw_enc $INPUT_DIR/3dmesh_3_3_400.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_3_3_400.log
./build/cabw_enc $INPUT_DIR/3dmesh_4_4_5.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_4_4_5.log
./build/cabw_enc $INPUT_DIR/3dmesh_4_4_68.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_4_4_68.log
./build/cabw_enc $INPUT_DIR/3dmesh_4_4_137.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_4_4_137.log
./build/cabw_enc $INPUT_DIR/3dmesh_4_4_200.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_4_4_200.log
./build/cabw_enc $INPUT_DIR/3dmesh_5_5_7.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_5_5_7.log
./build/cabw_enc $INPUT_DIR/3dmesh_5_5_35.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_5_5_35.log
./build/cabw_enc $INPUT_DIR/3dmesh_5_5_70.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_5_5_70.log
./build/cabw_enc $INPUT_DIR/3dmesh_5_5_100.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_5_5_100.log
./build/cabw_enc $INPUT_DIR/3dmesh_6_6_8.txt     --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_6_6_8.log
./build/cabw_enc $INPUT_DIR/3dmesh_6_6_36.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_6_6_36.log
./build/cabw_enc $INPUT_DIR/3dmesh_6_6_72.txt    --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_6_6_72.log
./build/cabw_enc $INPUT_DIR/3dmesh_6_6_100.txt   --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/3dmesh_6_6_100.log
