.PHONY: clean compile 
.DEFAULT_GOAL: compile

COMPILER = g++
CCFLAGS = -Wall
TMP_DIR = tmp
BUILD_DIR = build
SRC_DIR = src
# CLEAN_IGNORE = "makefile|.git|.gitignore|.vscode|README.md"

OUT_FILE = run.out



compile: $(BUILD_DIR)/ $(OUT_FILE)

clean: 
	-@rm -r $(TMP_DIR)/
	-@rm -r $(BUILD_DIR)/
	# ls -A | grep -vE $(CLEAN_IGNORE) | xargs -rt rm

$(OUT_FILE): $(SRC_DIR)/run.cpp
	$(COMPILER) -pthread $(CCFLAGS) -o $@ $^
	-@mv *.o $(BUILD_DIR)

$(BUILD_DIR)/:
	if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi