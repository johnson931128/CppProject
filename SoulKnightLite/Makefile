CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude

BIN_DIR  := bin
BUILD_DIR:= build
SRC_DIR  := src

# 自動尋找 src/ 底下所有的 .cpp 檔，並替換為對應的 .o 檔路徑
SRCS     := $(wildcard $(SRC_DIR)/*.cpp)
OBJS     := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

TARGET   := $(BIN_DIR)/SoulKnightLite

.PHONY: all clean

all: $(TARGET)

# 連結 (Linking) 步驟：將所有 .o 檔組合成執行檔
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 編譯 (Compiling) 步驟：將每個 .cpp 檔獨立編譯為 .o 檔
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理編譯產物
clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*
