PRECISION ?= 100

CppC = g++
CXXFLAGS = -O3 -std=c++20 -I${INCLUDE_DIR}

SRC_DIR = src
INCLUDE_DIR = lib
TEST_DIR = tests
BIN_DIR = bin

TEST_SRC = $(TEST_DIR)/Tests.cpp
PI_SRC = Pi_Calc.cpp
LONG_NUMBER_SRC = $(SRC_DIR)/LongNumber.cpp

PI_EXEC = ${BIN_DIR}/pi
TEST_EXEC = ${BIN_DIR}/test

all: $(PI_EXEC) $(TEST_EXEC)

$(PI_EXEC): $(PI_SRC) $(LONG_NUMBER_SRC)
	@mkdir -p $(@D)
	@$(CppC) $(CXXFLAGS) $^ -o $@

$(TEST_EXEC): $(TEST_SRC) $(LONG_NUMBER_SRC)
	@mkdir -p $(@D)
	@$(CppC) $(CXXFLAGS) $^ -o $@

clean:
	@rm -rf $(BIN_DIR)

pi: $(PI_EXEC)
	@${PI_EXEC} $(PRECISION)

test: $(TEST_EXEC)
	@${TEST_EXEC}

.PHONY: all clean pi test