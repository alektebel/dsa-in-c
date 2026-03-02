/**
 * Fault-Tolerant Stack Implementation
 */

#include "fault_tolerant_stack.h"
#include <stdlib.h>
#include <string.h>

/* Check whether a cell is valid (not corrupted). */
static bool cell_valid(const FTCell *cell) {
    return cell->magic == FT_MAGIC && cell->value == cell->value_copy;
}

/* Write a value into a cell with checksum. */
static void cell_write(FTCell *cell, int value) {
    cell->magic = FT_MAGIC;
    cell->value = value;
    cell->value_copy = value;
}

FTStack *ft_stack_create(int capacity, int delta) {
    if (capacity <= 0) return NULL;
    FTStack *stack = (FTStack *)malloc(sizeof(FTStack));
    if (!stack) return NULL;
    stack->storage = (FTCell *)calloc((size_t)capacity, sizeof(FTCell));
    if (!stack->storage) { free(stack); return NULL; }
    stack->capacity = capacity;
    stack->top = 0;         /* top=0 means empty; top=i means i elements */
    stack->delta = (delta > 0) ? delta : FT_DELTA;
    return stack;
}

void ft_stack_destroy(FTStack *stack) {
    if (!stack) return;
    free(stack->storage);
    free(stack);
}

bool ft_stack_push(FTStack *stack, int value) {
    if (!stack || stack->top >= stack->capacity) return false;
    cell_write(&stack->storage[stack->top], value);
    stack->top++;
    return true;
}

bool ft_stack_pop(FTStack *stack, int *value) {
    /* Scan backward from top, skipping corrupted cells (up to delta). */
    if (!stack || stack->top == 0) return false;
    int skipped = 0;
    while (stack->top > 0 && skipped <= stack->delta) {
        stack->top--;
        const FTCell *cell = &stack->storage[stack->top];
        if (cell_valid(cell)) {
            if (value) *value = cell->value;
            return true;
        }
        skipped++;
    }
    return false;
}

bool ft_stack_peek(const FTStack *stack, int *value) {
    if (!stack || stack->top == 0) return false;
    int pos = stack->top - 1;
    int scanned = 0;
    while (pos >= 0 && scanned <= stack->delta) {
        const FTCell *cell = &stack->storage[pos];
        if (cell_valid(cell)) {
            if (value) *value = cell->value;
            return true;
        }
        pos--; scanned++;
    }
    return false;
}

bool ft_stack_is_empty(const FTStack *stack) {
    return !stack || stack->top == 0;
}

int ft_stack_size(const FTStack *stack) {
    return stack ? stack->top : 0;
}

void ft_stack_inject_fault(FTStack *stack, int pos) {
    if (!stack || pos < 0 || pos >= stack->capacity) return;
    /* Corrupt the magic number to simulate a bit-flip */
    stack->storage[pos].magic ^= 0xFFFFFFFFu;
}
