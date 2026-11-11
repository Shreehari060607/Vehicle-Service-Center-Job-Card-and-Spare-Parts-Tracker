# Directories
SRC_DIR   = src
INC_DIR   = include
TEST_DIR  = tests
BUILD_DIR = build

# Output Executables (.exe used across platforms for Makefile simplicity)
TARGET   = $(BUILD_DIR)/service_center.exe
TEST_BIN = $(BUILD_DIR)/run_tests.exe

# Compiler Flags
CC       = gcc
CFLAGS   = -Wall -Wextra -Wpedantic -std=c11 -I$(INC_DIR) -MMD -MP

CXX      = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++17 -I$(INC_DIR)

# Source & Object Files
SRC      = $(wildcard $(SRC_DIR)/*.c)
OBJ      = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
# Exclude main.o when linking tests so test runner supplies main() via gtest_main
LIB_OBJ  = $(filter-out $(BUILD_DIR)/main.o,$(OBJ))

TEST_SRC = $(wildcard $(TEST_DIR)/*.cpp)

# Phony Targets
.PHONY: all run test clean

# Default Target
all: $(TARGET)

# Link Application Executable
$(TARGET): $(OBJ) | $(BUILD_DIR)
	$(CC) $(OBJ) -o $@

# Compile C Source Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create Build Directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run Application
run: $(TARGET)
	./$(TARGET)

# Build and Run Unit Tests
test: $(TEST_BIN)
	./$(TEST_BIN)

# Link Unit Test Executable with Google Test
$(TEST_BIN): $(LIB_OBJ) $(TEST_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(LIB_OBJ) -o $@ -lgtest -lgtest_main -pthread

# Clean Build Artifacts
clean:
	rm -rf $(BUILD_DIR)

# Include Auto-Generated Header Dependency (.d) Files
-include $(wildcard $(BUILD_DIR)/*.d)
