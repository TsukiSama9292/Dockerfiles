#!/bin/bash
# 測試用（使用 awk 提高效能）
awk 'BEGIN {
  sum = 0
  for (i = 0; i < 10000000; i++) {
    sum += i
  }
  print "Sum:", sum
}'