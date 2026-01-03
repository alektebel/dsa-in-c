# Makefile for DSA-in-C Project
# Compiles all data structures and algorithms

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 -g
AR = ar
ARFLAGS = rcs

# Directories
TREES_DIR = trees
LISTS_DIR = lists
HEAPS_DIR = heaps
HASH_DIR = hash
SEARCH_DIR = search_algorithms
STRING_DIR = string_matching
SYNC_DIR = synchronization
BUILD_DIR = build
LIB_DIR = lib

# Source files
TREES_SRC = $(wildcard $(TREES_DIR)/*.c)
LISTS_SRC = $(wildcard $(LISTS_DIR)/*.c)
HEAPS_SRC = $(wildcard $(HEAPS_DIR)/*.c)
HASH_SRC = $(wildcard $(HASH_DIR)/*.c)
SEARCH_SRC = $(wildcard $(SEARCH_DIR)/*.c)
STRING_SRC = $(wildcard $(STRING_DIR)/*.c)
SYNC_SRC = $(wildcard $(SYNC_DIR)/*.c)

# Object files
TREES_OBJ = $(TREES_SRC:$(TREES_DIR)/%.c=$(BUILD_DIR)/trees_%.o)
LISTS_OBJ = $(LISTS_SRC:$(LISTS_DIR)/%.c=$(BUILD_DIR)/lists_%.o)
HEAPS_OBJ = $(HEAPS_SRC:$(HEAPS_DIR)/%.c=$(BUILD_DIR)/heaps_%.o)
HASH_OBJ = $(HASH_SRC:$(HASH_DIR)/%.c=$(BUILD_DIR)/hash_%.o)
SEARCH_OBJ = $(SEARCH_SRC:$(SEARCH_DIR)/%.c=$(BUILD_DIR)/search_%.o)
STRING_OBJ = $(STRING_SRC:$(STRING_DIR)/%.c=$(BUILD_DIR)/string_%.o)
SYNC_OBJ = $(SYNC_SRC:$(SYNC_DIR)/%.c=$(BUILD_DIR)/sync_%.o)

ALL_OBJ = $(TREES_OBJ) $(LISTS_OBJ) $(HEAPS_OBJ) $(HASH_OBJ) $(SEARCH_OBJ) $(STRING_OBJ) $(SYNC_OBJ)

# Library
LIBRARY = $(LIB_DIR)/libdsa.a

# Default target
.PHONY: all
all: $(LIBRARY)

# Create directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Build library
$(LIBRARY): $(BUILD_DIR) $(LIB_DIR) $(ALL_OBJ)
	$(AR) $(ARFLAGS) $@ $(ALL_OBJ)
	@echo "Library created: $@"

# Compile rules for each directory
$(BUILD_DIR)/trees_%.o: $(TREES_DIR)/%.c
	$(CC) $(CFLAGS) -I$(TREES_DIR) -c $< -o $@

$(BUILD_DIR)/lists_%.o: $(LISTS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LISTS_DIR) -c $< -o $@

$(BUILD_DIR)/heaps_%.o: $(HEAPS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(HEAPS_DIR) -c $< -o $@

$(BUILD_DIR)/hash_%.o: $(HASH_DIR)/%.c
	$(CC) $(CFLAGS) -I$(HASH_DIR) -c $< -o $@

$(BUILD_DIR)/search_%.o: $(SEARCH_DIR)/%.c
	$(CC) $(CFLAGS) -I$(SEARCH_DIR) -c $< -o $@

$(BUILD_DIR)/string_%.o: $(STRING_DIR)/%.c
	$(CC) $(CFLAGS) -I$(STRING_DIR) -c $< -o $@

$(BUILD_DIR)/sync_%.o: $(SYNC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(SYNC_DIR) -c $< -o $@

# Clean
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR) example
	@echo "Cleaned build artifacts"

# Example program
example: $(LIBRARY) example.c
	$(CC) $(CFLAGS) -o example example.c -I. -L$(LIB_DIR) -ldsa
	@echo "Example program built: ./example"

# Help
.PHONY: help
help:
	@echo "DSA-in-C Makefile"
	@echo "=================="
	@echo "Targets:"
	@echo "  all     - Build the DSA library (default)"
	@echo "  example - Build the example program"
	@echo "  clean   - Remove build artifacts"
	@echo "  help    - Show this help message"
	@echo ""
	@echo "The library will be created at: $(LIBRARY)"
	@echo "Include headers from respective directories"

# Show what will be built
.PHONY: info
info:
	@echo "Source files:"
	@echo "  Trees: $(TREES_SRC)"
	@echo "  Lists: $(LISTS_SRC)"
	@echo "  Heaps: $(HEAPS_SRC)"
	@echo "  Hash: $(HASH_SRC)"
	@echo "  Search: $(SEARCH_SRC)"
	@echo "  String: $(STRING_SRC)"
	@echo "  Sync: $(SYNC_SRC)"
