CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# 找到所有的 .cpp 文件
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# 将 .cpp 文件名转换为 .o 文件名，并指定 obj 目录
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# 可执行文件名
EXECUTABLE = $(BIN_DIR)/slime_battle

# 默认目标
all: $(EXECUTABLE)

# 链接目标文件生成可执行文件
$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# 编译源文件生成目标文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 创建必要的目录
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# 清理编译产生的文件
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# 声明伪目标
.PHONY: all clean