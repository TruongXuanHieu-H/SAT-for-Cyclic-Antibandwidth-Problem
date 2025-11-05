#!/bin/bash

TIME_LIMIT=1800
MEMORY_LIMIT=30000
SYMMETRY_BREAK="highest-degree"
WORKER_COUNT=8
DATASET_DIR="../../datasets/unknow_optimal/random_generated_graph_2013"
LOG_DIR="../../logs/unknow_optimal/random_generated_graph_2013/binarysearchfromUB_highestdegree_8workers"
ADD_CONFIGS="--binary-search-from-ub"

mkdir -p "$LOG_DIR"

../../build/cabw_enc $DATASET_DIR/p1_100_200 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p1_100_200.log
../../build/cabw_enc $DATASET_DIR/p2_100_200 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p2_100_200.log
../../build/cabw_enc $DATASET_DIR/p3_100_200 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p3_100_200.log
../../build/cabw_enc $DATASET_DIR/p4_100_200 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p4_100_200.log
../../build/cabw_enc $DATASET_DIR/p5_100_200 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p5_100_200.log
../../build/cabw_enc $DATASET_DIR/p6_100_200 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p6_100_200.log
../../build/cabw_enc $DATASET_DIR/p7_100_200 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p7_100_200.log
../../build/cabw_enc $DATASET_DIR/p8_100_200 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p8_100_200.log
../../build/cabw_enc $DATASET_DIR/p9_100_200 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p9_100_200.log
../../build/cabw_enc $DATASET_DIR/p10_100_200 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p10_100_200.log

../../build/cabw_enc $DATASET_DIR/p11_100_600 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p11_100_600.log
../../build/cabw_enc $DATASET_DIR/p12_100_600 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p12_100_600.log
../../build/cabw_enc $DATASET_DIR/p13_100_600 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p13_100_600.log
../../build/cabw_enc $DATASET_DIR/p14_100_600 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p14_100_600.log
../../build/cabw_enc $DATASET_DIR/p15_100_600 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p15_100_600.log
../../build/cabw_enc $DATASET_DIR/p16_100_600 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p16_100_600.log
../../build/cabw_enc $DATASET_DIR/p17_100_600 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p17_100_600.log
../../build/cabw_enc $DATASET_DIR/p18_100_600 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p18_100_600.log
../../build/cabw_enc $DATASET_DIR/p19_100_600 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p19_100_600.log
../../build/cabw_enc $DATASET_DIR/p20_100_600 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p20_100_600.log

../../build/cabw_enc $DATASET_DIR/p21_200_400 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p21_200_400.log
../../build/cabw_enc $DATASET_DIR/p22_200_400 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p22_200_400.log
../../build/cabw_enc $DATASET_DIR/p23_200_400 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p23_200_400.log
../../build/cabw_enc $DATASET_DIR/p24_200_400 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p24_200_400.log
../../build/cabw_enc $DATASET_DIR/p25_200_400 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p25_200_400.log
../../build/cabw_enc $DATASET_DIR/p26_200_400 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p26_200_400.log
../../build/cabw_enc $DATASET_DIR/p27_200_400 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p27_200_400.log
../../build/cabw_enc $DATASET_DIR/p28_200_400 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p28_200_400.log
../../build/cabw_enc $DATASET_DIR/p29_200_400 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p29_200_400.log
../../build/cabw_enc $DATASET_DIR/p30_200_400 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p30_200_400.log

../../build/cabw_enc $DATASET_DIR/p31_200_2000 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p31_200_2000.log
../../build/cabw_enc $DATASET_DIR/p32_200_2000 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p32_200_2000.log
../../build/cabw_enc $DATASET_DIR/p33_200_2000 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p33_200_2000.log
../../build/cabw_enc $DATASET_DIR/p34_200_2000 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p34_200_2000.log
../../build/cabw_enc $DATASET_DIR/p35_200_2000 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p35_200_2000.log
../../build/cabw_enc $DATASET_DIR/p36_200_2000 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p36_200_2000.log
../../build/cabw_enc $DATASET_DIR/p37_200_2000 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p37_200_2000.log
../../build/cabw_enc $DATASET_DIR/p38_200_2000 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p38_200_2000.log
../../build/cabw_enc $DATASET_DIR/p39_200_2000 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p39_200_2000.log
../../build/cabw_enc $DATASET_DIR/p40_200_2000 --ladder -limit-real-time $TIME_LIMIT -limit-memory $MEMORY_LIMIT -symmetry-break $SYMMETRY_BREAK -worker-count $WORKER_COUNT $ADD_CONFIGS 2>&1 | tee $LOG_DIR/p40_200_2000.log
