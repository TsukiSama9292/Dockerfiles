# 配置驅動 OJ 微服務 Makefile

# 變數定義
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LIBS = -lcjson
HARNESS = harness
CONFIG = config.json
RESULT = result.json

# 默認目標
.PHONY: all build test clean help examples

all: build

# 編譯 harness
build: $(HARNESS)

$(HARNESS): harness.c
	@echo "編譯 harness..."
	$(CC) $(CFLAGS) harness.c -o $(HARNESS) $(LIBS)
	@echo "✅ 編譯完成"

# 運行測試
test: build
	@echo "運行測試..."
	./$(HARNESS) $(CONFIG) $(RESULT)
	@echo "測試完成，結果保存在 $(RESULT)"

# 運行測試並顯示詳細錯誤（如果有的話）
test-verbose: build
	@echo "運行測試（詳細模式）..."
	./$(HARNESS) $(CONFIG) $(RESULT)
	@echo "測試完成，結果保存在 $(RESULT)"
	@if [ -f $(RESULT) ]; then \
		echo "=== 測試結果 ==="; \
		cat $(RESULT) | jq '.' 2>/dev/null || cat $(RESULT); \
		if grep -q "COMPILE_ERROR\|ERROR" $(RESULT); then \
			echo ""; \
			echo "=== 錯誤詳情 ==="; \
			cat $(RESULT) | jq -r '.stderr // .error // "無詳細錯誤信息"' 2>/dev/null; \
		fi \
	fi

# 顯示結果
show-result:
	@if [ -f $(RESULT) ]; then \
		echo "=== 測試結果 ==="; \
		cat $(RESULT) | jq '.' 2>/dev/null || cat $(RESULT); \
	else \
		echo "結果文件不存在，請先運行 make test"; \
	fi

# 運行所有範例
examples: build
	@echo "=== 運行所有範例 ==="
	@echo "1. 基本範例..."
	@cp user.c user_backup.c
	@cp user.c user_temp.c
	@./$(HARNESS) config.json result_basic.json
	@echo "   狀態: $$(cat result_basic.json | grep -o '\"status\":\"[^\"]*\"' | cut -d: -f2 | tr -d '\"')"
	
	@echo "2. 平方範例..."
	@cp user_squares.c user.c
	@./$(HARNESS) config_squares.json result_squares.json
	@echo "   狀態: $$(cat result_squares.json | grep -o '\"status\":\"[^\"]*\"' | cut -d: -f2 | tr -d '\"')"
	
	@echo "3. 階乘範例..."
	@cp user_factorial.c user.c
	@./$(HARNESS) config_factorial.json result_factorial.json
	@echo "   狀態: $$(cat result_factorial.json | grep -o '\"status\":\"[^\"]*\"' | cut -d: -f2 | tr -d '\"')"
	
	@echo "4. 進階範例..."
	@cp user_advanced.c user.c
	@./$(HARNESS) config_advanced.json result_advanced.json
	@echo "   狀態: $$(cat result_advanced.json | grep -o '\"status\":\"[^\"]*\"' | cut -d: -f2 | tr -d '\"')"
	
	@cp user_temp.c user.c
	@rm -f user_temp.c user_backup.c
	@echo "✅ 所有範例執行完成"

# 清理生成文件
clean:
	@echo "清理文件..."
	rm -f $(HARNESS) test_runner solve.h test_main.c
	rm -f result*.json
	@echo "✅ 清理完成"

# 深度清理（包含範例結果）
clean-all: clean
	rm -f user_backup.c user_temp.c

# 檢查依賴
check-deps:
	@echo "檢查依賴..."
	@which gcc > /dev/null || (echo "❌ GCC 未安裝" && exit 1)
	@pkg-config --exists libcjson || (echo "❌ libcjson 未安裝" && exit 1)
	@echo "✅ 所有依賴已滿足"

# 幫助信息
help:
	@echo "配置驅動 OJ 微服務"
	@echo ""
	@echo "可用目標:"
	@echo "  build        - 編譯 harness"
	@echo "  test         - 運行基本測試"
	@echo "  test-verbose - 運行測試並顯示詳細錯誤信息"
	@echo "  show-result  - 顯示測試結果"
	@echo "  examples     - 運行所有範例"
	@echo "  clean        - 清理生成文件"
	@echo "  clean-all    - 深度清理"
	@echo "  check-deps   - 檢查依賴"
	@echo "  help         - 顯示此幫助"
	@echo ""
	@echo "使用方式:"
	@echo "  make build              # 編譯"
	@echo "  make test               # 測試"
	@echo "  make test-verbose       # 詳細錯誤測試"
	@echo "  make examples           # 運行所有範例"
	@echo ""
	@echo "手動使用:"
	@echo "  ./harness config.json result.json"

# 創建新題目模板
new-problem:
	@read -p "題目名稱: " name; \
	echo "創建題目: $$name"; \
	echo '{"solve_params":[{"name":"result","input_value":0}],"expected":{"result":42}}' > config_$$name.json; \
	echo 'int solve(int *result) { *result = 42; return 0; }' > user_$$name.c; \
	echo "✅ 已創建 config_$$name.json 和 user_$$name.c"
