# 配置驅動 OJ 微服務 C++ 版本 Makefile

# 變數定義
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
HARNESS = harness
CONFIG = config.json
RESULT = result.json

# 默認目標
.PHONY: all build test clean help examples test-all

all: build

# 編譯 harness
build: $(HARNESS)

$(HARNESS): harness.cpp json.hpp
	@echo "編譯 C++ harness..."
	$(CXX) $(CXXFLAGS) harness.cpp -o $(HARNESS)
	@echo "✅ 編譯完成"

# 運行測試
test: build
	@echo "運行基本測試..."
	./$(HARNESS) $(CONFIG) $(RESULT)
	@echo "測試完成，結果保存在 $(RESULT)"

# 運行測試並顯示詳細錯誤（如果有的話）
test-verbose: build
	@echo "運行測試（詳細模式）..."
	./$(HARNESS) $(CONFIG) $(RESULT)
	@echo "測試完成，結果保存在 $(RESULT)"
	@if [ -f $(RESULT) ]; then \
		echo "=== 測試結果 ==="; \
		cat $(RESULT); \
		echo ""; \
	fi

# 顯示結果
show-result:
	@if [ -f $(RESULT) ]; then \
		echo "=== 測試結果 ==="; \
		cat $(RESULT); \
	else \
		echo "❌ 結果文件不存在，請先運行測試"; \
	fi

# 運行所有示例
test-all: build
	@echo "🧪 運行所有示例測試..."
	@echo ""
	@echo "1️⃣ 基本數學運算測試"
	@echo "========================"
	@if [ -f user_basic.cpp ]; then \
		cp user_basic.cpp user.cpp; \
	fi
	./$(HARNESS) config.json result_basic.json
	@cat result_basic.json
	@echo ""
	@echo ""
	@echo "2️⃣ 字符串處理測試"
	@echo "======================="
	@if [ -f user_string.cpp ]; then \
		cp user_string.cpp user.cpp; \
		./$(HARNESS) config_string.json result_string.json; \
		cat result_string.json; \
	fi
	@echo ""
	@echo ""
	@echo "3️⃣ 容器操作測試"
	@echo "====================="
	@if [ -f user_vector.cpp ]; then \
		cp user_vector.cpp user.cpp; \
		./$(HARNESS) config_vector.json result_vector.json; \
		cat result_vector.json; \
	fi
	@echo ""
	@echo ""
	@echo "4️⃣ 階乘計算測試"
	@echo "====================="
	@if [ -f user_factorial.cpp ]; then \
		cp user_factorial.cpp user.cpp; \
		./$(HARNESS) config_factorial.json result_factorial.json; \
		cat result_factorial.json; \
	fi
	@echo ""
	@echo "✅ 所有測試完成"

# 清理生成的文件
clean:
	@echo "清理生成的文件..."
	rm -f $(HARNESS)
	rm -f test_main.cpp
	rm -f test_runner
	rm -f result*.json
	@echo "✅ 清理完成"

# 深度清理（包括用戶代碼備份）
clean-all: clean
	@echo "深度清理..."
	rm -f user_backup.cpp
	rm -f *.o
	@echo "✅ 深度清理完成"

# 顯示幫助信息
help:
	@echo "配置驅動 OJ 微服務 C++ 版本"
	@echo ""
	@echo "可用的命令："
	@echo "  make build        - 編譯 harness"
	@echo "  make test         - 運行基本測試"
	@echo "  make test-verbose - 運行詳細測試"
	@echo "  make test-all     - 運行所有示例測試"
	@echo "  make show-result  - 顯示測試結果"
	@echo "  make clean        - 清理生成的文件"
	@echo "  make clean-all    - 深度清理"
	@echo "  make help         - 顯示此幫助信息"
	@echo ""
	@echo "示例用法："
	@echo "  make build                           # 編譯"
	@echo "  make test                           # 運行默認測試"
	@echo "  make CONFIG=config_string.json test # 使用指定配置測試"
	@echo ""
	@echo "配置文件："
	@echo "  config.json           - 基本數學運算"
	@echo "  config_string.json    - 字符串處理"
	@echo "  config_vector.json    - 容器操作"
	@echo "  config_factorial.json - 階乘計算"

# 創建示例配置
examples:
	@echo "📝 可用的示例配置文件："
	@echo ""
	@if [ -f config.json ]; then \
		echo "✅ config.json - 基本數學運算"; \
		echo "   輸入: a=3, b=4"; \
		echo "   期望: a=6, b=9"; \
		echo ""; \
	fi
	@if [ -f config_string.json ]; then \
		echo "✅ config_string.json - 字符串處理"; \
		echo "   輸入: text=\"hello\", length=0"; \
		echo "   期望: text=\"HELLO\", length=5"; \
		echo ""; \
	fi
	@if [ -f config_vector.json ]; then \
		echo "✅ config_vector.json - 容器操作"; \
		echo "   輸入: numbers=[1,2,3,4,5], sum=0"; \
		echo "   期望: numbers=[2,4,6,8,10], sum=30"; \
		echo ""; \
	fi
	@if [ -f config_factorial.json ]; then \
		echo "✅ config_factorial.json - 階乘計算"; \
		echo "   輸入: n=5, result=1"; \
		echo "   期望: n=5, result=120"; \
		echo ""; \
	fi
	@echo "💡 使用 'make CONFIG=<配置文件> test' 運行指定配置的測試"

# 檢查編譯環境
check-env:
	@echo "🔍 檢查編譯環境..."
	@echo ""
	@echo "C++ 編譯器:"
	@$(CXX) --version || echo "❌ C++ 編譯器未找到"
	@echo ""
	@echo "C++17 支持測試:"
	@echo 'int main() { auto x = 42; return 0; }' | $(CXX) -std=c++17 -x c++ - -o /tmp/cpp17_test 2>/dev/null && echo "✅ C++17 支持正常" || echo "❌ C++17 支持有問題"
	@rm -f /tmp/cpp17_test
	@echo ""
	@echo "編譯標誌: $(CXXFLAGS)"

# 快速測試（用於開發）
quick-test: build
	@echo "⚡ 快速測試..."
	./$(HARNESS) $(CONFIG) $(RESULT) && echo "✅ 測試通過" || echo "❌ 測試失敗"

# 性能測試
benchmark: build
	@echo "🏃‍♂️ 性能測試..."
	@for i in {1..5}; do \
		echo "第 $$i 次運行:"; \
		time ./$(HARNESS) $(CONFIG) $(RESULT); \
		echo ""; \
	done

# 調試模式編譯
debug: CXXFLAGS += -DDEBUG -O0
debug: build
	@echo "🐛 調試版本編譯完成"

# 發佈模式編譯
release: CXXFLAGS += -DNDEBUG -O3
release: build
	@echo "🚀 發佈版本編譯完成"
