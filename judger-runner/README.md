# 程式碼 - 編譯 & 執行

> 基於 Linux 與 Python 基本庫，編譯&執行程式碼，並且獲得資訊(編譯錯誤、執行標準輸出、執行錯誤、執行時間、最大記憶體佔用...等資訊)

## 支援語言與鏡像，Dockerfile 儲存庫 Link

- Bash 鏡像 TAG: [`bash-5.2`, `bash-5.3`, `bash-latest`](https://github.com/TsukiSama9292/Dockerfiles/blob/main/judger-runner/bash/Dockerfile)
- C/C++ 鏡像 TAG: [`gcc-14`, `gcc-15`](https://github.com/TsukiSama9292/Dockerfiles/blob/main/judger-runner/gcc/Dockerfile)
- Go 鏡像 TAG: [`golang-1.24`, `go-latest`](https://github.com/TsukiSama9292/Dockerfiles/blob/main/judger-runner/golang/Dockerfile)
- Java 鏡像 TAG: [`jdk-11`, `jdk-17`, `jdk-22`](https://github.com/TsukiSama9292/Dockerfiles/blob/main/judger-runner/jdk/Dockerfile)
- Kotlin 鏡像 TAG: [`kotlin-1.3-alpine`, `kotlin-1.4-alpine`](https://github.com/TsukiSama9292/Dockerfiles/blob/main/judger-runner/kotlin/Dockerfile)
- C# 鏡像 TAG: [`net-8.0-alpine`, `net-9.0-alpine`](https://github.com/TsukiSama9292/Dockerfiles/blob/main/judger-runner/net/Dockerfile)
- JavaScript/TypeScript 鏡像 TAG: [`node-18`, `node-20`, `node-22`, `node-lts`](https://github.com/TsukiSama9292/Dockerfiles/blob/main/judger-runner/node/Dockerfile)
- PHP 鏡像 TAG: [`php-8.2`, `php-8.3`, `php-8.4`, `php-latest`](https://github.com/TsukiSama9292/Dockerfiles/blob/main/judger-runner/php/Dockerfile)
- Python 鏡像 TAG: [`python-3.9`, `python-3.10`, `python-3.11`, `python-3.12` `python-3.13`, `python-latest`](https://github.com/TsukiSama9292/Dockerfiles/blob/main/judger-runner/python/Dockerfile)
- Ruby 鏡像 TAG: [`ruby-3.3`, `ruby-3.4`, `ruby-latest`](https://github.com/TsukiSama9292/Dockerfiles/blob/main/judger-runner/ruby/Dockerfile)  
- Rust 鏡像 TAG: [`rust-1.88`, `rust-latest`](https://github.com/TsukiSama9292/Dockerfiles/blob/main/judger-runner/rust/Dockerfile)
- SQL 鏡像 TAG: [`sqlite`](https://github.com/TsukiSama9292/Dockerfiles/blob/main/judger-runner/sqlite/Dockerfile)

## 腳本參數介紹

```bash
python3 runner.py --filename [script_path] --db [db_path] --cleanup
```

--filename [script_path] : 指定程式碼路徑  
--db [db_path]: 指定資料庫檔案路徑  
--cleanup : 清除編譯後的檔案  

```json
{
    "stdout": str,           # 子程序標準輸出（文字內容）
    "stderr": str,           # 子程序標準錯誤輸出（錯誤訊息）
    "returncode": int,       # 子程序返回碼，0 通常代表成功，非 0 表示錯誤
    "time_wall_sec": float,  # （僅執行時）牆鐘時間（秒），從啟動到結束的真實經過時間
    "cpu_utime": float,      # （僅執行時）CPU 使用者態時間（秒），程式運算時間
    "cpu_stime": float,      # （僅執行時）CPU 系統態時間（秒），系統呼叫或 I/O 花費的時間
    "maxrss_mb": float       # （僅執行時）最大常駐記憶體大小，單位 MB（峰值記憶體使用量）
}
```

## C 語言(編譯)
### 輸入
```bash
docker pull tsukisama9292/judger-runner:gcc-14
docker run -t -d --name gcc-14 tsukisama9292/judger-runner:gcc-14
# 直接執行
docker exec -it gcc-14 bash -c "python3 runner.py --filename test.c --cleanup"
# 使用 harness 得到精準 solve 函數結果與
docker exec -it gcc-14 bash -c "python3 runner.py --filename user.c --use-harness --cleanup"
```
### 預期結果
```json
{'stage': 'run', 'stdout': 'Sum: 49999995000000\n', 'stderr': '', 'returncode': 0, 'time_wall_sec': 0.09726309776306152, 'cpu_utime': 0.08184899999999999, 'cpu_stime': 0.002738, 'maxrss_mb': 13.30078125}
```

## Python(直譯)
### 執行
```bash
docker pull tsukisama9292/judger-runner:python-3.11
docker run -t -d --name python-311 tsukisama9292/judger-runner:python-3.11
docker exec -it python-311 bash -c "python3 runner.py --filename test.py"
```
### 預期輸出
```bash
{'stage': 'run', 'stdout': 'Sum: 49999995000000\n', 'stderr': '', 'returncode': 0, 'time_wall_sec': 0.43921661376953125, 'cpu_utime': 0.272481, 'cpu_stime': 0.15753599999999998, 'maxrss_mb': 390.12890625}
```

## SQL
### 執行
```bash
docker pull tsukisama9292/judger-runner:sqlite
docker run -t -d --name sqlite tsukisama9292/judger-runner:sqlite
docker exec -it sqlite sh -c "python3 runner.py --filename test.sql --db test.db"
```
### 預期結果
```bash
{'stage': 'run', 'stdout': '10000\n', 'stderr': '', 'returncode': 0, 'time_wall_sec': 0.02073526382446289, 'cpu_utime': 0.003175, 'cpu_stime': 0.0015869999999999999, 'maxrss_mb': 11.63671875}
```