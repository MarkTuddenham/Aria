.PHONY: clean compile run
.DEFAULT_GOAL: compile

CC := g++
CCFLAGS := -pthread -Wall -Wextra -D_GLIBCXX_USE_CXX11_ABI=0
LINKFLAGS := 

RM := rm

TMP_PATH := ./tmp/
BUILD_PATH := ./build/
SRC_PATH := ./src/
INC_PATH := -I ./include
# CLEAN_IGNORE = "makefile|.git|.gitignore|.vscode|README.md"

TARGET := run.out

# Files to compile
OBJS = run.o board.o piece.o
OBJ = $(patsubst %,$(BUILD_PATH)%,$(OBJS))


compile: $(BUILD_PATH) $(TARGET)

run: compile
	@echo [RUNNING] $(TARGET)
	@./$(TARGET)

# Build .o first
$(BUILD_PATH)%.o: $(SRC_PATH)%.cpp
	@echo [CC] $<
	@$(CC) $(CCFLAGS) -o $@ -c $< $(INC_PATH)

# Build final binary
$(TARGET): $(OBJ)
	@echo [INFO] Creating Binary Executable :- $(TARGET)
	@$(CC) -o $@ $^ $(LINKFLAGS)

clean:
	@echo "[Cleaning]"
	@$(RM) -rfv $(BUILD_PATH)*
	@$(RM) -rfv $(TMP_PATH)*
	@$(RM) -rfv $(TARGET)

$(BUILD_PATH):
	if [ ! -d $(BUILD_PATH) ]; then mkdir $(BUILD_PATH); fi