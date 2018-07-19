EXE = diffusion
TEST_EXE = test_diffusion

SRC_DIR = .
TEST_SRC_DIR = test
OBJ_DIR = .
TEST_OBJ_DIR = test
BIN_DIR = .
TEST_BIN_DIR = test
TEST_LIB_DIR = test

SRC = $(wildcard $(SRC_DIR)/*.c)
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
OBJ_WITHOUT_MAIN = $(filter-out $(OBJ_DIR)/main.o, $(OBJ))
OBJ_WITHOUT_PY = $(filter-out $(OBJ_DIR)/diffusion_py.o, $(OBJ))
OBJ_WITHOUT_MAIN_PY = $(filter-out $(OBJ_DIR)/diffusion_py.o, $(OBJ_WITHOUT_MAIN))
TEST_OBJ = $(patsubst $(TEST_SRC_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TEST_SRC))
BIN = $(wildcard $(BIN_DIR)/*.out)
TEST_BIN = $(wildcard $(TEST_BIN_DIR)/*.out)
LIB =
TEST_LIB = $(wildcard $(TEST_LIB_DIR)/*.a)

CC = gcc
CFLAGS += -Wall -O2
TEST_CFLAGS += -pthread
INC = -I.
INC_TEST = -Itest

default: compile

all: compile

compile: $(EXE)

$(EXE): $(OBJ_WITHOUT_PY)
	$(CC) $^ -o $(BIN_DIR)/$@.out $(LIB) -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

test: $(TEST_EXE)

$(TEST_EXE): $(TEST_OBJ) $(OBJ_WITHOUT_MAIN_PY)
	$(CC) $^ -o $(TEST_BIN_DIR)/$@.out $(TEST_LIB) $(LIB) -lm

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(TEST_CFLAGS) $(INC) $(INC_TEST) -c $< -o $@

# travis: $(TEST_EXE)
#
# $(TEST_EXE): $(TEST_OBJ) $(OBJ_WITHOUT_MAIN)
# 	$(CXX) $^ -o $(TEST_BIN_DIR)/$@.out -lgtest $(LIB)
#
# $(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
# 	$(CXX) $(CXXFLAGS) $(TEST_CXXFLAGS) $(INC) -c $< -o $@

debug: CFLAGS += -DDEBUG -g
debug: $(EXE)

.PHONY: python
python:
	python setup.py install_lib

.PHONY: clean
clean:
	$(RM) $(OBJ)
	$(RM) $(BIN)
	$(RM) $(TEST_OBJ)
	$(RM) $(TEST_BIN)
	rm -rf ./build
	$(RM) *.so
