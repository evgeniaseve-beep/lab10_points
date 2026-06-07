CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -fPIC -Iinclude -lm
LDFLAGS = -shared
SANITIZE_FLAGS = -fsanitize=address,undefined -g

SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BUILD_DIR = build

LIB = libpoint_set.so
DEMO = point_demo
TEST_BIN = point_tests

all: $(BUILD_DIR)/$(LIB) $(BUILD_DIR)/$(DEMO)

$(BUILD_DIR)/$(LIB): $(SRC_DIR)/point_set.c
    mkdir -p $(BUILD_DIR)
    $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/$(DEMO): $(SRC_DIR)/main.c $(BUILD_DIR)/$(LIB)
    $(CC) $(CFLAGS) -L$(BUILD_DIR) -Wl,-rpath=$(BUILD_DIR) -o $@ $< -lpoint_set -lm

$(BUILD_DIR)/$(TEST_BIN): $(TEST_DIR)/test_point_set.c $(BUILD_DIR)/$(LIB)
    $(CC) $(CFLAGS) -L$(BUILD_DIR) -Wl,-rpath=$(BUILD_DIR) -o $@ $< -lpoint_set -lm

tests: $(BUILD_DIR)/$(TEST_BIN)
    $(BUILD_DIR)/$(TEST_BIN)

py-test: $(BUILD_DIR)/$(LIB)
    python3 $(TEST_DIR)/test_point_set.py

run: $(BUILD_DIR)/$(DEMO)
    $(BUILD_DIR)/$(DEMO)

syntax:
    $(CC) -fsyntax-only $(CFLAGS) $(SRC_DIR)/point_set.c

analyze:
    mkdir -p reports
    cppcheck --enable=all --suppress=missingIncludeSystem -Iinclude $(SRC_DIR)/point_set.c 2> reports/cppcheck.txt || true
    @echo "Analysis complete. Check reports/cppcheck.txt"

sanitize: CFLAGS += $(SANITIZE_FLAGS)
sanitize: clean $(BUILD_DIR)/$(TEST_BIN)
    $(BUILD_DIR)/$(TEST_BIN)

docs-html:
    doxygen docs/Doxyfile

clean:
    rm -rf $(BUILD_DIR) reports

.PHONY: all clean run tests py-test syntax analyze sanitize docs-html