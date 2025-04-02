CXX = g++
CXXFLAGS = -g -Wall -Werror -std=c++11
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LDFLAGS = -lncurses

# Create directory structure for object files
DIRS = $(OBJ_DIR) $(OBJ_DIR)/core $(OBJ_DIR)/generation $(OBJ_DIR)/io $(OBJ_DIR)/path_finding $(OBJ_DIR)/movement

# Source files (assuming you've renamed .c files to .cpp)
CORE_SRC = $(wildcard $(SRC_DIR)/core/*.cpp)
GEN_SRC = $(wildcard $(SRC_DIR)/generation/*.cpp)
IO_SRC = $(wildcard $(SRC_DIR)/io/*.cpp)
PATH_FINDING_SRC = $(wildcard $(SRC_DIR)/path_finding/*.cpp)
MOVEMENT_SRC = $(wildcard $(SRC_DIR)/movement/*.cpp)

MAIN_SRC = $(SRC_DIR)/main.cpp

# Object files
CORE_OBJ = $(patsubst $(SRC_DIR)/core/%.cpp, $(OBJ_DIR)/core/%.o, $(CORE_SRC))
GEN_OBJ = $(patsubst $(SRC_DIR)/generation/%.cpp, $(OBJ_DIR)/generation/%.o, $(GEN_SRC))
IO_OBJ = $(patsubst $(SRC_DIR)/io/%.cpp, $(OBJ_DIR)/io/%.o, $(IO_SRC))
PATH_FINDING_OBJ = $(patsubst $(SRC_DIR)/path_finding/%.cpp, $(OBJ_DIR)/path_finding/%.o, $(PATH_FINDING_SRC))
MOVEMENT_OBJ = $(patsubst $(SRC_DIR)/movement/%.cpp, $(OBJ_DIR)/movement/%.o, $(MOVEMENT_SRC))

MAIN_OBJ = $(OBJ_DIR)/main.o

# All objects
ALL_OBJ = $(CORE_OBJ) $(GEN_OBJ) $(IO_OBJ) $(PATH_FINDING_OBJ) $(MAIN_OBJ) $(MOVEMENT_OBJ)

# Target executable
TARGET = dungeon

all: dirs $(TARGET)

dirs:
    @mkdir -p $(DIRS)

$(TARGET): $(ALL_OBJ)
    $(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile main.cpp
$(OBJ_DIR)/main.o: $(MAIN_SRC)
    $(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile core files
$(OBJ_DIR)/core/%.o: $(SRC_DIR)/core/%.cpp $(INCLUDE_DIR)/dungeon.h
    $(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile generation files
$(OBJ_DIR)/generation/%.o: $(SRC_DIR)/generation/%.cpp $(INCLUDE_DIR)/dungeon.h
    $(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile IO files
$(OBJ_DIR)/io/%.o: $(SRC_DIR)/io/%.cpp $(INCLUDE_DIR)/dungeon.h $(INCLUDE_DIR)/load_save.h
    $(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile path_finding files
$(OBJ_DIR)/path_finding/%.o: $(SRC_DIR)/path_finding/%.cpp $(INCLUDE_DIR)/dijkstra.h
    $(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile movement files
$(OBJ_DIR)/movement/%.o: $(SRC_DIR)/movement/%.cpp $(INCLUDE_DIR)/dungeon.h
    $(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
    rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all dirs clean