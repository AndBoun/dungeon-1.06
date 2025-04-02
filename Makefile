CXX = g++
CXXFLAGS = -g -Wall -Werror -std=c++17
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LDFLAGS = -lncurses

# Create directory structure for object files
DIRS = $(OBJ_DIR) $(OBJ_DIR)/dungeon $(OBJ_DIR)/dungeon/base $(OBJ_DIR)/utils $(OBJ_DIR)/io

# Source files (assuming you've renamed .c files to .cpp)
DUNGEON_SRC = $(wildcard $(SRC_DIR)/dungeon/*.cpp)
DUNGEON_BASE_SRC = $(wildcard $(SRC_DIR)/dungeon/base/*.cpp)
IO_SRC = $(wildcard $(SRC_DIR)/io/*.cpp)
UTILS_SRC = $(wildcard $(SRC_DIR)/utils/*.cpp)
MAIN_SRC = $(SRC_DIR)/main.cpp

# Object files
DUNGEON_OBJ = $(patsubst $(SRC_DIR)/dungeon/%.cpp, $(OBJ_DIR)/dungeon/%.o, $(DUNGEON_SRC))
DUNGEON_BASE_OBJ = $(patsubst $(SRC_DIR)/dungeon/base/%.cpp, $(OBJ_DIR)/dungeon/base/%.o, $(DUNGEON_BASE_SRC))
IO_OBJ = $(patsubst $(SRC_DIR)/io/%.cpp, $(OBJ_DIR)/io/%.o, $(IO_SRC))
UTILS_OBJ = $(patsubst $(SRC_DIR)/utils/%.cpp, $(OBJ_DIR)/utils/%.o, $(UTILS_SRC))
MAIN_OBJ = $(OBJ_DIR)/main.o

# All objects
ALL_OBJ = $(DUNGEON_OBJ) $(DUNGEON_BASE_OBJ) $(IO_OBJ) $(UTILS_OBJ) $(MAIN_OBJ)

# Target executable
TARGET = dungeon.out

all: dirs $(TARGET)

dirs:
	@mkdir -p $(DIRS)

$(TARGET): $(ALL_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile main.cpp
$(OBJ_DIR)/main.o: $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile dungeon files
$(OBJ_DIR)/dungeon/%.o: $(SRC_DIR)/dungeon/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile dungeon/base files
$(OBJ_DIR)/dungeon/base/%.o: $(SRC_DIR)/dungeon/base/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile io files
$(OBJ_DIR)/io/%.o: $(SRC_DIR)/io/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile utils files
$(OBJ_DIR)/utils/%.o: $(SRC_DIR)/utils/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all dirs clean