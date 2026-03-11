/**
 * Grep – Pattern Search in Text
 *
 * "grep" (Global Regular Expression Print) is a classical Unix utility that
 * searches for lines matching a pattern.  Internally it combines:
 *   1. Pattern compilation  – convert a human-readable pattern expression
 *      into an efficient matching structure.
 *   2. Text scanning        – scan the input text line by line, testing
 *      each line against the compiled pattern.
 *   3. Result collection    – record matching line numbers, column offsets,
 *      and the matched text.
 *
 * Pattern syntax supported by this template:
 *   .       – matches any single character
 *   *       – zero or more of the preceding element
 *   +       – one or more of the preceding element
 *   ?       – zero or one of the preceding element
 *   ^       – anchors the match to the start of the line
 *   $       – anchors the match to the end of the line
 *   [abc]   – character class (matches any character in the set)
 *   [^abc]  – negated character class
 *   [a-z]   – character range inside a class
 *   \c      – literal character c (escape special characters)
 *   |       – alternation: (pat1|pat2) matches either
 *
 * Algorithm overview:
 *   Compiling a pattern builds a simple NFA (Non-deterministic Finite
 *   Automaton) via Thompson's construction.  Matching is performed by
 *   simulating the NFA with the powerset (subset) construction, giving
 *   O(m) compile time and O(n) match time per line for a pattern of
 *   length m and a line of length n.
 *
 * Used in:
 * - Text editors and IDEs (search, highlight, replace)
 * - Log analysis pipelines
 * - Source code analysis tools (ripgrep, ag, git grep)
 * - Compiler lexers (tokenisation by regex)
 * - Intrusion detection systems (snort / suricata rule patterns)
 */

#ifndef GREP_H
#define GREP_H

#include <stddef.h>
#include <stdbool.h>

/* -------------------------------------------------------------------------
 * Pattern type
 * ------------------------------------------------------------------------- */

/**
 * Complexity level of the pattern, used to choose the matching engine.
 */
typedef enum {
    GREP_PATTERN_LITERAL,   /* Plain string – no metacharacters          */
    GREP_PATTERN_WILDCARD,  /* Shell-style glob (*, ?)                   */
    GREP_PATTERN_REGEX      /* Full regex subset (see header description) */
} GrepPatternType;

/* -------------------------------------------------------------------------
 * Options
 * ------------------------------------------------------------------------- */

/**
 * Search options that modify grep behaviour.
 */
typedef struct {
    bool case_insensitive; /* -i: treat upper/lower as equivalent          */
    bool invert_match;     /* -v: select lines that do NOT match           */
    bool whole_word;       /* -w: pattern must match a complete word token */
    bool whole_line;       /* -x: pattern must match the entire line       */
    bool count_only;       /* -c: only return the total count of matches   */
    bool line_numbers;     /* -n: record line numbers in results           */
    size_t max_matches;    /* Maximum number of matches (0 = unlimited)    */
} GrepOptions;

/* -------------------------------------------------------------------------
 * Results
 * ------------------------------------------------------------------------- */

/**
 * A single match found within a line.
 */
typedef struct {
    size_t line_number;     /* 1-based line number in the input text      */
    size_t col_start;       /* 0-based start column of the match          */
    size_t col_end;         /* 0-based end column (exclusive)             */
    const char *line_start; /* Pointer to the start of the matched line   */
    size_t line_len;        /* Length of the matched line (excl. newline) */
} GrepMatch;

/**
 * Collection of all matches found by a grep search.
 */
typedef struct {
    GrepMatch *matches;    /* Heap-allocated array of match records  */
    size_t     n_matches;  /* Number of matches stored               */
    size_t     capacity;   /* Allocated capacity of matches array    */
    size_t     total_count;/* Total count including skipped matches  */
} GrepResult;

/* -------------------------------------------------------------------------
 * Compiled pattern (opaque)
 * ------------------------------------------------------------------------- */

/**
 * Compiled grep pattern – internal NFA/DFA representation.
 * Created by grep_compile(); freed by grep_free_pattern().
 */
typedef struct GrepPattern GrepPattern;

/* -------------------------------------------------------------------------
 * Pattern compilation
 * ------------------------------------------------------------------------- */

/**
 * Compile a pattern string into an efficient matching structure.
 *
 * @param pattern      Pattern string (see header for supported syntax)
 * @param pattern_type Syntax level (LITERAL, WILDCARD, or REGEX)
 * @param options      Search options (for case_insensitive flag at compile)
 * @return Compiled pattern, or NULL on parse error
 */
GrepPattern* grep_compile(const char *pattern,
                          GrepPatternType pattern_type,
                          GrepOptions options);

/**
 * Free a compiled pattern.
 *
 * @param pat Pattern to free (safe to call with NULL)
 */
void grep_free_pattern(GrepPattern *pat);

/* -------------------------------------------------------------------------
 * Matching against a single line
 * ------------------------------------------------------------------------- */

/**
 * Test whether a compiled pattern matches anywhere in a line.
 *
 * @param pat       Compiled pattern
 * @param line      Line to test (need not be NUL-terminated)
 * @param line_len  Length of the line in bytes
 * @param col_start Output: start column of match (may be NULL)
 * @param col_end   Output: end column (exclusive) of match (may be NULL)
 * @return true if the pattern matches (at least once) in the line
 */
bool grep_match_line(const GrepPattern *pat,
                     const char *line,
                     size_t line_len,
                     size_t *col_start,
                     size_t *col_end);

/* -------------------------------------------------------------------------
 * Searching text buffers
 * ------------------------------------------------------------------------- */

/**
 * Search a NUL-terminated text buffer for all lines matching the pattern.
 *
 * Lines are separated by '\n'.  The last line may omit the trailing newline.
 *
 * @param pat     Compiled pattern
 * @param text    NUL-terminated input text
 * @param options Search options
 * @return Heap-allocated GrepResult (free with grep_result_free()), or NULL
 */
GrepResult* grep_search_text(const GrepPattern *pat,
                             const char *text,
                             GrepOptions options);

/**
 * Convenience wrapper that compiles the pattern and searches in one call.
 *
 * @param pattern      Pattern string
 * @param pattern_type Syntax level
 * @param text         NUL-terminated input text
 * @param options      Search options
 * @return Heap-allocated GrepResult, or NULL on error
 */
GrepResult* grep_search(const char *pattern,
                        GrepPatternType pattern_type,
                        const char *text,
                        GrepOptions options);

/**
 * Count matching lines without collecting detailed match records.
 *
 * @param pat     Compiled pattern
 * @param text    NUL-terminated input text
 * @param options Search options
 * @return Number of matching lines (or non-matching lines if invert_match set)
 */
size_t grep_count(const GrepPattern *pat,
                  const char *text,
                  GrepOptions options);

/* -------------------------------------------------------------------------
 * Result management
 * ------------------------------------------------------------------------- */

/**
 * Free a GrepResult returned by grep_search_text() or grep_search().
 *
 * @param result Result to free (safe to call with NULL)
 */
void grep_result_free(GrepResult *result);

/**
 * Print grep results to stdout in the classic grep output format:
 *   <line_number>:<matched_line>
 *
 * @param result  Results to print
 * @param options Options used when searching (to show/hide line numbers)
 */
void grep_print_results(const GrepResult *result, GrepOptions options);

/* -------------------------------------------------------------------------
 * Utility helpers
 * ------------------------------------------------------------------------- */

/**
 * Return a GrepOptions struct initialised to sensible defaults
 * (all flags false, max_matches = 0).
 */
GrepOptions grep_default_options(void);

/**
 * Quick check: does the pattern appear at least once in the text?
 *
 * @param pattern     Plain literal pattern string
 * @param text        NUL-terminated text to search
 * @param ignore_case Whether to ignore case
 * @return true if found
 */
bool grep_contains(const char *pattern,
                   const char *text,
                   bool ignore_case);

#endif /* GREP_H */
