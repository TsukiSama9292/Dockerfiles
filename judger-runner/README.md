# 程式碼 - 編譯 & 執行

## C 語言
### 輸入
```bash
docker pull tsukisama9292/judger-runner:gcc-14
docker run -t -d --name gcc-14 tsukisama9292/judger-runner:gcc-14
### 測試
docker exec -it gcc-14 bash -c "python3 runner.py --filename test.c --cleanup"
```
### 預期結果
```json
{'stage': 'run', 'stdout': 'Sum: 49999995000000\n', 'stderr': '', 'returncode': 0, 'time_wall_sec': 0.09726309776306152, 'cpu_utime': 0.08184899999999999, 'cpu_stime': 0.002738, 'maxrss_mb': 13.30078125}
```

## C++
### 輸入
```bash
docker pull tsukisama9292/judger-runner:gcc-14
docker run -t -d --name gcc-14 tsukisama9292/judger-runner:gcc-14
### 測試
docker exec -it gcc-14 bash -c "python3 runner.py --filename test.cpp --cleanup"
```
### 預期結果
```json
{'stage': 'run', 'stdout': 'Sum: 49999995000000\n', 'stderr': '', 'returncode': 0, 'time_wall_sec': 0.09913969039916992, 'cpu_utime': 0.083413, 'cpu_stime': 0.0036769999999999997, 'maxrss_mb': 13.109375}
```

## Python
### 執行
```bash
docker pull tsukisama9292/judger-runner:python-3.11
docker run -t -d --name python-311 tsukisama9292/judger-runner:python-3.11
### 測試
docker exec -it python-311 bash -c "python3 runner.py --filename test.py --cleanup"
```
### 預期結果
```json
{'stage': 'run', 'stdout': 'Sum: 49999995000000\n', 'stderr': '', 'returncode': 0, 'time_wall_sec': 0.4228065013885498, 'cpu_utime': 0.269628, 'cpu_stime': 0.149334, 'maxrss_mb': 390.30859375}
```

## Java
### 輸入
```bash
docker pull tsukisama9292/judger-runner:jdk-17
docker run -t -d --name jdk-17 tsukisama9292/judger-runner:jdk-17
### 測試
docker exec -it jdk-17 bash -c "python3 runner.py --filename Test.java --cleanup"
```
### 預期輸出
```json
{'stage': 'run', 'stdout': 'Sum: 49999995000000\n', 'stderr': '', 'returncode': 0, 'time_wall_sec': 0.12264513969421387, 'cpu_utime': 0.098898, 'cpu_stime': 0.040565, 'maxrss_mb': 37.25390625}
```