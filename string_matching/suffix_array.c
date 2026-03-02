/**
 * Suffix Array Implementation
 */

#include "suffix_array.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ---- Simple O(n log^2 n) construction (placeholder for SA-IS) ---- */

static int compare_suffix(const char *text, int n, int a, int b) {
    while (a < n && b < n && text[a] == text[b]) { a++; b++; }
    if (a == n) return -1;
    if (b == n) return 1;
    return (unsigned char)text[a] - (unsigned char)text[b];
}

typedef struct { const char *text; int n; } SortCtx;
static SortCtx g_ctx; /* Used by qsort comparator */

static int sa_cmp(const void *pa, const void *pb) {
    return compare_suffix(g_ctx.text, g_ctx.n, *(const int *)pa, *(const int *)pb);
}

SuffixArray *sa_build(const char *text) {
    if (!text) return NULL;
    SuffixArray *sa = (SuffixArray *)malloc(sizeof(SuffixArray));
    if (!sa) return NULL;
    sa->n = (int)strlen(text);
    sa->text = (char *)malloc((size_t)(sa->n + 1));
    sa->sa   = (int *)malloc((size_t)sa->n * sizeof(int));
    sa->rank = (int *)malloc((size_t)sa->n * sizeof(int));
    sa->lcp  = (int *)calloc((size_t)sa->n, sizeof(int));
    if (!sa->text || !sa->sa || !sa->rank || !sa->lcp) {
        sa_destroy(sa); return NULL;
    }
    memcpy(sa->text, text, (size_t)(sa->n + 1));

    /* --- Build SA (simple O(n log^2 n), TODO: replace with SA-IS) --- */
    for (int i = 0; i < sa->n; i++) sa->sa[i] = i;
    g_ctx.text = sa->text; g_ctx.n = sa->n;
    qsort(sa->sa, (size_t)sa->n, sizeof(int), sa_cmp);

    /* --- Build rank array --- */
    for (int i = 0; i < sa->n; i++) sa->rank[sa->sa[i]] = i;

    /* --- Build LCP array via Kasai's algorithm --- */
    /* TODO: implement Kasai's O(n) LCP construction.
     * int h = 0;
     * for (int i = 0; i < n; i++) {
     *     if (rank[i] > 0) {
     *         int j = sa[rank[i] - 1];
     *         while (i+h < n && j+h < n && text[i+h] == text[j+h]) h++;
     *         lcp[rank[i]] = h;
     *         if (h > 0) h--;
     *     }
     * } */

    return sa;
}

void sa_destroy(SuffixArray *sa) {
    if (!sa) return;
    free(sa->text);
    free(sa->sa);
    free(sa->rank);
    free(sa->lcp);
    free(sa);
}

/* Binary search helpers */
static int sa_lower_bound(const SuffixArray *sa, const char *pattern, int m) {
    int lo = 0, hi = sa->n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (strncmp(sa->text + sa->sa[mid], pattern, (size_t)m) < 0)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

static int sa_upper_bound(const SuffixArray *sa, const char *pattern, int m) {
    int lo = 0, hi = sa->n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (strncmp(sa->text + sa->sa[mid], pattern, (size_t)m) <= 0)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

int sa_search(const SuffixArray *sa, const char *pattern) {
    if (!sa || !pattern) return -1;
    int m = (int)strlen(pattern);
    int lo = sa_lower_bound(sa, pattern, m);
    if (lo < sa->n && strncmp(sa->text + sa->sa[lo], pattern, (size_t)m) == 0)
        return sa->sa[lo];
    return -1;
}

int sa_count(const SuffixArray *sa, const char *pattern) {
    if (!sa || !pattern) return 0;
    int m = (int)strlen(pattern);
    return sa_upper_bound(sa, pattern, m) - sa_lower_bound(sa, pattern, m);
}

bool sa_find_all(const SuffixArray *sa, const char *pattern,
                 int *positions, int *count) {
    if (!sa || !pattern || !positions || !count) return false;
    int m = (int)strlen(pattern);
    int lo = sa_lower_bound(sa, pattern, m);
    int hi = sa_upper_bound(sa, pattern, m);
    *count = hi - lo;
    for (int i = lo; i < hi; i++) positions[i - lo] = sa->sa[i];
    return true;
}

void sa_longest_repeat(const SuffixArray *sa, int *start, int *length) {
    /* TODO: scan LCP array for the maximum value; the corresponding
     * SA entry gives the start position. */
    if (start) *start = 0;
    if (length) *length = 0;
    if (!sa) return;
    int best = 0, best_idx = 0;
    for (int i = 1; i < sa->n; i++) {
        if (sa->lcp[i] > best) { best = sa->lcp[i]; best_idx = i; }
    }
    if (start) *start = sa->sa[best_idx];
    if (length) *length = best;
}

void sa_longest_common_substring(const char *text1, const char *text2,
                                 int *start1, int *start2, int *length) {
    /* TODO: Build generalized SA over text1+'$'+text2+'#', then scan LCP
     * array for the maximum value at an index where one suffix comes from
     * text1 and the other from text2. */
    if (start1) *start1 = 0;
    if (start2) *start2 = 0;
    if (length) *length = 0;
    (void)text1; (void)text2;
}
