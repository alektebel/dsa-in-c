/**
 * Arithmetic Coding Implementation
 */

#include "arithmetic_coding.h"
#include <stdlib.h>
#include <string.h>

ACModel ac_model_build(const uint32_t freqs[AC_ALPHA_SIZE]) {
    ACModel model;
    model.adaptive = false;
    model.cumulative[0] = 0;
    for (int i = 0; i < AC_ALPHA_SIZE; i++)
        model.cumulative[i + 1] = model.cumulative[i] + (freqs[i] > 0 ? freqs[i] : 1);
    return model;
}

ACModel ac_model_uniform(void) {
    ACModel model;
    model.adaptive = false;
    for (int i = 0; i <= AC_ALPHA_SIZE; i++)
        model.cumulative[i] = (uint32_t)i;
    return model;
}

void ac_model_update(ACModel *model, int s) {
    /* TODO: Increment count for symbol s and update all cumulative entries
     * for symbols > s.  Scale down all counts by 2 if total exceeds AC_SCALE
     * to prevent overflow. */
    if (!model || s < 0 || s >= AC_ALPHA_SIZE) return;
}

void ac_encoder_init(ACEncoder *enc, uint8_t *out, size_t out_cap) {
    if (!enc) return;
    enc->low = 0;
    enc->high = AC_SCALE - 1;
    enc->pending_bits = 0;
    enc->out = out;
    enc->out_len = 0;
    enc->out_cap = out_cap;
}

/* Helper: output a bit (and any pending opposite bits). */
static void ac_emit_bit(ACEncoder *enc, int bit) {
    /* TODO: Emit bit to output buffer (byte-pack), then emit pending_bits
     * opposite bits. */
    (void)enc; (void)bit;
}

bool ac_encode_symbol(ACEncoder *enc, const ACModel *model, int s) {
    /* TODO: Implement arithmetic encoding step.
     * range = high - low + 1
     * total = model->cumulative[AC_ALPHA_SIZE]
     * high = low + range * model->cumulative[s+1] / total - 1
     * low  = low + range * model->cumulative[s]   / total
     * Then renormalize: while high/low share leading bits, emit those bits. */
    if (!enc || !model || s < 0 || s >= AC_ALPHA_SIZE) return false;
    return false;
}

void ac_encoder_finish(ACEncoder *enc, size_t *out_len) {
    /* TODO: Flush remaining interval bits (emit enough bits to uniquely
     * identify the final interval). */
    if (!enc) return;
    if (out_len) *out_len = enc->out_len;
}

void ac_decoder_init(ACDecoder *dec, const uint8_t *in, size_t in_len) {
    if (!dec) return;
    dec->low = 0;
    dec->high = AC_SCALE - 1;
    dec->value = 0;
    dec->in = in;
    dec->in_len = in_len;
    dec->in_pos = 0;
    dec->bit_pos = 7;
    /* TODO: pre-fill dec->value with the first log2(AC_SCALE) bits from in. */
}

int ac_decode_symbol(ACDecoder *dec, const ACModel *model) {
    /* TODO: Implement arithmetic decoding step.
     * range = high - low + 1
     * total = model->cumulative[AC_ALPHA_SIZE]
     * scaled_value = (value - low + 1) * total / range - 1 (roughly)
     * Binary search in model->cumulative for the symbol s such that
     *   cumulative[s] <= scaled_value < cumulative[s+1]
     * Then update low/high as in encoding, renormalize, read new bits. */
    if (!dec || !model) return -1;
    return -1;
}

uint8_t *ac_compress(const uint8_t *input, size_t in_len,
                     const ACModel *model, size_t *out_len) {
    if (!input || in_len == 0 || !model || !out_len) return NULL;
    size_t buf_cap = in_len + 64;
    uint8_t *buf = (uint8_t *)calloc(buf_cap, 1);
    if (!buf) return NULL;
    ACEncoder enc;
    ac_encoder_init(&enc, buf, buf_cap);
    for (size_t i = 0; i < in_len; i++) {
        if (!ac_encode_symbol(&enc, model, input[i])) {
            free(buf); return NULL;
        }
    }
    ac_encoder_finish(&enc, out_len);
    return buf;
}

uint8_t *ac_decompress(const uint8_t *input, size_t in_len,
                       const ACModel *model, size_t sym_cnt, size_t *out_len) {
    if (!input || in_len == 0 || !model || !out_len) return NULL;
    uint8_t *buf = (uint8_t *)malloc(sym_cnt);
    if (!buf) return NULL;
    ACDecoder dec;
    ac_decoder_init(&dec, input, in_len);
    for (size_t i = 0; i < sym_cnt; i++) {
        int s = ac_decode_symbol(&dec, model);
        if (s < 0) { free(buf); return NULL; }
        buf[i] = (uint8_t)s;
    }
    *out_len = sym_cnt;
    return buf;
}
