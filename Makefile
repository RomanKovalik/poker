BUILD = debug
OUT_DIR = $(BUILD)

OUT_NAME = $(OUT_DIR)/poker

SRC = $(wildcard Curie/*.cpp) $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=$(OUT_DIR)/%.o)
DEP = $(OBJ:.o=.d)

CXX = g++
COMPILER_FLAGS.debug = -Wall -Werror -Wfatal-errors -I.
COMPILER_FLAGS.release = -Wall -Werror -Wfatal-errors -I. -O3 -DNDEBUG

LINKER_FLAGS = -lpthread -lSDL2 -lSDL2_image

all: dirs $(OUT_NAME)

.PHONY: release
release: dirs $(OUT_NAME)

.PHONY: dirs
dirs:
	mkdir -p $(OUT_DIR)/Curie

$(OUT_DIR)/%.o: %.cpp
	$(CXX) -MMD -c $(COMPILER_FLAGS.$(BUILD)) $< -o $@

$(OUT_NAME): $(OBJ)
	$(CXX) $(OBJ) $(LINKER_FLAGS) -o $@

.PHONY: clean
clean:
	rm -rf $(OUT_DIR)

-include $(OUT_DIR)/$(DEP)
