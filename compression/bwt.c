/**
 * Burrows-Wheeler Transform (BWT) Implementation
 */

#include "bwt.h"
#include <stdlib.h>
#include <string.h>

/* ---- Sort helper for cyclic rotations ---- */

typedef struct { const uint8_t *base; int n; int pos; } RotCmp;
static RotCmp g_rot; /* Used by qsort comparator */

static int rot_cmp(const void *pa, const void *pb) {
    int a = *(const int *)pa;
    int b = *(const int *)pb;
    for (int i = 0; i < g_rot.n; i++) {
        int ca = g_rot.base[(a + i) % g_rot.n];
        int cb = g_rot.base[(b + i) % g_rot.n];
        if (ca != cb) return ca - cb;
    }
    return 0;
}

BWTResult bwt_forward(const uint8_t *data, int n) {
    BWTResult result = {NULL, -1, 0};
    if (!data || n <= 0) return result;

    /* Append sentinel 0x00 */
    int N = n + 1;
    uint8_t *s = (uint8_t *)malloc((size_t)N);
    if (!s) return result;
    memcpy(s, data, (size_t)n);
    s[n] = 0x00;  /* Sentinel: must be lexicographically smallest */

    /* Build suffix array for cyclic rotations */
    int *sa = (int *)malloc((size_t)N * sizeof(int));
    if (!sa) { free(s); return result; }
    for (int i = 0; i < N; i++) sa[i] = i;
    g_rot.base = s; g_rot.n = N;
    qsort(sa, (size_t)N, sizeof(int), rot_cmp);

    /* Collect BWT (last column) */
    result.L = (uint8_t *)malloc((size_t)N);
    if (!result.L) { free(sa); free(s); return result; }
    result.n = N;
    for (int i = 0; i < N; i++) {
        result.L[i] = s[(sa[i] + N - 1) % N];
        if (sa[i] == 0) result.index = i;
    }

    free(sa); free(s);
    return result;
}

void bwt_free(BWTResult *r) {
    if (r) { free(r->L); r->L = NULL; }
}

bool bwt_inverse(const uint8_t *L, int n, int index, uint8_t *out) {
    /* TODO: Implement LF-mapping inversion.
     * 1. Compute F (sorted L) and count[] for each character.
     * 2. Compute LF[i] = C[L[i]] + rank(L[i], i)
     *    where C[c] = number of chars in L less than c,
     *    and rank(c,i) = number of times c appears in L[0..i-1].
     * 3. Starting at index, follow LF n-1 times to reconstruct original data.
     *
     * Simple O(n^2) placeholder:
     */
    if (!L || !out || n <= 0) return false;

    /* Build F (sorted copy of L) */
    uint8_t *F = (uint8_t *)malloc((size_t)n);
    int *lf   = (int *)malloc((size_t)n * sizeof(int));
    int *cnt  = (int *)calloc(256, sizeof(int));
    if (!F || !lf || !cnt) { free(F); free(lf); free(cnt); return false; }
    memcpy(F, L, (size_t)n);

    /* Counting sort to produce F */
    for (int i = 0; i < n; i++) cnt[(unsigned char)L[i]]++;
    int *C = (int *)calloc(256, sizeof(int));
    if (!C) { free(F); free(lf); free(cnt); return false; }
    for (int c = 1; c < 256; c++) C[c] = C[c-1] + cnt[c-1];
    /* F[C[c]..C[c]+cnt[c]-1] = c */
    int *occ = (int *)calloc(256, sizeof(int));
    if (!occ) { free(C); free(F); free(lf); free(cnt); return false; }
    /* Build LF mapping */
    for (int i = 0; i < n; i++) {
        int c = (unsigned char)L[i];
        lf[i] = C[c] + occ[c];
        occ[c]++;
    }

    /* Reconstruct */
    int cur = index;
    for (int i = n - 2; i >= 0; i--) {
        cur = lf[cur];
        out[i] = L[cur];
    }

    free(F); free(lf); free(cnt); free(C); free(occ);
    return true;
}

uint8_t *bwt_compress(const uint8_t *data, int n, int *out_len) {
    /* TODO: Implement BWT -> MTF -> RLE -> (optionally Huffman) pipeline.
     * For now, just return the raw BWT output with the index prepended. */
    if (!data || n <= 0 || !out_len) return NULL;
    BWTResult r = bwt_forward(data, n);
    if (!r.L) return NULL;
    /* Prepend 4-byte index */
    uint8_t *out = (uint8_t *)malloc((size_t)(r.n + 4));
    if (!out) { bwt_free(&r); return NULL; }
    out[0] = (uint8_t)((r.index >> 24) & 0xff);
    out[1] = (uint8_t)((r.index >> 16) & 0xff);
    out[2] = (uint8_t)((r.index >>  8) & 0xff);
    out[3] = (uint8_t)( r.index        & 0xff);
    memcpy(out + 4, r.L, (size_t)r.n);
    *out_len = r.n + 4;
    bwt_free(&r);
    return out;
}

uint8_t *bwt_decompress(const uint8_t *data, int in_len, int *out_len) {
    /* TODO: Invert the bwt_compress pipeline. */
    if (!data || in_len < 5 || !out_len) return NULL;
    int index = ((int)data[0] << 24) | ((int)data[1] << 16) |
                ((int)data[2] <<  8) |  (int)data[3];
    int n = in_len - 4;
    const uint8_t *L = data + 4;
    /* Recovered output is one byte shorter (sentinel removed) */
    uint8_t *out = (uint8_t *)malloc((size_t)(n - 1));
    if (!out) return NULL;
    if (!bwt_inverse(L, n, index, out)) { free(out); return NULL; }
    *out_len = n - 1;
    return out;
}
