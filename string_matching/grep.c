/**
 * Grep Pattern Search Implementation
 */

#include "grep.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

/* -------------------------------------------------------------------------
 * Internal NFA node types
 * Used by Thompson's construction to build the pattern NFA.
 * ------------------------------------------------------------------------- */

/** NFA state for Thompson's construction. */
typedef enum {
    NFA_CHAR,    /* Match a specific character (or . for any)    */
    NFA_CLASS,   /* Match a character class [...]                */
    NFA_SPLIT,   /* ε-transition split (used for *, +, ?, |)    */
    NFA_MATCH    /* Accepting state                              */
} NFAStateType;

/** Single NFA state (node). */
typedef struct NFAState {
    NFAStateType type;
    /* NFA_CHAR fields */
    char         ch;          /* Character to match (NFA_CHAR)                */
    bool         any_char;    /* True if this state matches any char (.)      */
    /* NFA_CLASS fields */
    bool         char_class[256]; /* character class membership lookup table  */
    bool         negate_class;    /* True if class is negated ([^...])        */
    /* Successor states */
    struct NFAState *out1;    /* Primary output transition                    */
    struct NFAState *out2;    /* Secondary output (ε-split, or NULL)          */
} NFAState;

/**
 * Compiled grep pattern – wraps the NFA start state and options.
 */
struct GrepPattern {
    NFAState       *start;         /* NFA entry state                  */
    NFAState      **states;        /* All allocated states (for free)  */
    size_t          n_states;      /* Number of allocated NFA states   */
    size_t          states_cap;    /* Allocated capacity               */
    GrepPatternType type;          /* Pattern syntax level             */
    bool            case_insensitive; /* Cached from compile options   */
    bool            anchored_start;   /* Pattern starts with ^         */
    bool            anchored_end;     /* Pattern ends with $           */
};

/* -------------------------------------------------------------------------
 * Internal: NFA state allocation
 * ------------------------------------------------------------------------- */

static NFAState* nfa_alloc_state(GrepPattern *pat, NFAStateType type) {
    // TODO: Allocate a new NFAState and register it in pat->states
    // 1. If pat->n_states == pat->states_cap, realloc and double capacity
    // 2. Allocate a new NFAState via calloc
    // 3. Set state->type = type
    // 4. Append to pat->states; pat->n_states++
    // 5. Return the new state
    (void)pat;
    (void)type;
    return NULL;
}

/* -------------------------------------------------------------------------
 * Pattern compilation
 * ------------------------------------------------------------------------- */

GrepPattern* grep_compile(const char *pattern,
                          GrepPatternType pattern_type,
                          GrepOptions options) {
    // TODO: Compile the pattern string into a GrepPattern NFA
    //
    // Allocation:
    // 1. malloc a GrepPattern; initialise fields
    // 2. pat->type = pattern_type
    // 3. pat->case_insensitive = options.case_insensitive
    //
    // For GREP_PATTERN_LITERAL:
    //   Build a chain of NFA_CHAR states (one per character) ending in NFA_MATCH
    //   If case_insensitive, tolower each character before storing it
    //   Time: O(m)
    //
    // For GREP_PATTERN_WILDCARD (glob-style):
    //   '*' → zero-or-more any-char (NFA_SPLIT loop)
    //   '?' → single any-char (NFA_CHAR with any_char=true)
    //   Other chars → NFA_CHAR literal
    //
    // For GREP_PATTERN_REGEX (Thompson's construction):
    //   Parse the regex and build NFA fragments:
    //     char  → single NFA_CHAR state
    //     .     → NFA_CHAR with any_char=true
    //     e*    → NFA_SPLIT: out1=e.start, out2=next; e.end → NFA_SPLIT
    //     e+    → e, then NFA_SPLIT: out1=e.start, out2=next
    //     e?    → NFA_SPLIT: out1=e.start, out2=next
    //     e1e2  → patch e1.end → e2.start
    //     e1|e2 → NFA_SPLIT: out1=e1.start, out2=e2.start
    //     [abc] → NFA_CLASS state with char_class bitmap set
    //     ^     → set pat->anchored_start = true (no state)
    //     $     → set pat->anchored_end = true (no state)
    //
    // 4. Append NFA_MATCH state at the end
    // 5. pat->start = root of the NFA; return pat
    (void)pattern;
    (void)pattern_type;
    (void)options;
    return NULL;
}

void grep_free_pattern(GrepPattern *pat) {
    // TODO: Free all states and the pattern struct
    // 1. if (!pat) return
    // 2. For i in [0, n_states): free(pat->states[i])
    // 3. free(pat->states)
    // 4. free(pat)
    (void)pat;
}

/* -------------------------------------------------------------------------
 * Matching
 * ------------------------------------------------------------------------- */

bool grep_match_line(const GrepPattern *pat,
                     const char *line,
                     size_t line_len,
                     size_t *col_start,
                     size_t *col_end) {
    // TODO: Run the NFA over the line and check for a match
    //
    // NFA simulation (Thompson's algorithm):
    // Maintain two sets of active states: current and next (use bitmaps or
    // arrays of NFAState pointers; size bounded by n_states).
    //
    // If anchored_start (^): only try starting from position 0
    // Otherwise: try starting from each position i in [0, line_len)
    //
    // For each start position i:
    //   current = ε-closure({pat->start})    ← include all ε-reachable states
    //   For each character line[pos] from i to line_len:
    //     c = case_insensitive ? tolower(line[pos]) : line[pos]
    //     next = {}
    //     For each state s in current:
    //       if s->type == NFA_CHAR and (s->any_char or s->ch == c):
    //         add ε-closure({s->out1}) to next
    //       if s->type == NFA_CLASS and char_class[c] ^ negate_class:
    //         add ε-closure({s->out1}) to next
    //     if NFA_MATCH is in current:
    //       match found at [i, pos); fill col_start, col_end; return true
    //     current = next
    //   if NFA_MATCH is in current (end of string):
    //     check anchored_end ($) if needed
    //     fill col_start = i, col_end = line_len; return true
    //
    // Return false if no match found at any start position
    (void)pat;
    (void)line;
    (void)line_len;
    (void)col_start;
    (void)col_end;
    return false;
}

/* -------------------------------------------------------------------------
 * Searching text buffers
 * ------------------------------------------------------------------------- */

GrepResult* grep_search_text(const GrepPattern *pat,
                             const char *text,
                             GrepOptions options) {
    // TODO: Iterate over lines of text and collect matches
    //
    // 1. Allocate GrepResult (initial capacity e.g. 16 matches)
    // 2. line_ptr = text; line_number = 1
    // 3. While *line_ptr != '\0':
    //    a. Find end of line: end = strchr(line_ptr, '\n') or end of string
    //    b. line_len = end - line_ptr
    //    c. matched = grep_match_line(pat, line_ptr, line_len, &col_start, &col_end)
    //    d. If (matched XOR options.invert_match):
    //         result->total_count++
    //         If !options.count_only AND
    //            (options.max_matches == 0 OR n_matches < max_matches):
    //           Grow result->matches if needed (realloc, double capacity)
    //           Fill GrepMatch: line_number, col_start, col_end, line_start, line_len
    //           result->n_matches++
    //    e. line_ptr = end + 1 (skip '\n'); line_number++
    // 4. Return result
    (void)pat;
    (void)text;
    (void)options;
    return NULL;
}

GrepResult* grep_search(const char *pattern,
                        GrepPatternType pattern_type,
                        const char *text,
                        GrepOptions options) {
    // TODO: Compile pattern then delegate to grep_search_text
    // 1. pat = grep_compile(pattern, pattern_type, options)
    // 2. result = grep_search_text(pat, text, options)
    // 3. grep_free_pattern(pat)
    // 4. Return result
    (void)pattern;
    (void)pattern_type;
    (void)text;
    (void)options;
    return NULL;
}

size_t grep_count(const GrepPattern *pat,
                  const char *text,
                  GrepOptions options) {
    // TODO: Count matching lines without storing individual matches
    // Similar to grep_search_text but only increment a counter
    // Consider setting options.count_only = true and delegating,
    // or implementing a lean loop for efficiency
    (void)pat;
    (void)text;
    (void)options;
    return 0;
}

/* -------------------------------------------------------------------------
 * Result management
 * ------------------------------------------------------------------------- */

void grep_result_free(GrepResult *result) {
    // TODO: Free the matches array and the result struct
    // 1. if (!result) return
    // 2. free(result->matches)
    // 3. free(result)
    (void)result;
}

void grep_print_results(const GrepResult *result, GrepOptions options) {
    // TODO: Print each match in classic grep format
    // For each match in result->matches:
    //   If options.line_numbers:
    //     printf("%zu:", match.line_number)
    //   printf("%.*s\n", (int)match.line_len, match.line_start)
    (void)result;
    (void)options;
}

/* -------------------------------------------------------------------------
 * Utility helpers
 * ------------------------------------------------------------------------- */

GrepOptions grep_default_options(void) {
    // TODO: Return a GrepOptions with all flags false and max_matches = 0
    GrepOptions opts;
    memset(&opts, 0, sizeof(opts));
    return opts;
}

bool grep_contains(const char *pattern,
                   const char *text,
                   bool ignore_case) {
    // TODO: Quick literal search (no full regex, no result collection)
    // 1. Build options: case_insensitive = ignore_case
    // 2. grep_search() with GREP_PATTERN_LITERAL
    // 3. found = result->n_matches > 0
    // 4. grep_result_free(); return found
    (void)pattern;
    (void)text;
    (void)ignore_case;
    return false;
}
