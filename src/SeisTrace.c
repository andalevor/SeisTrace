#include <m-try.h>

#include "SeisTrace.h"
#include <assert.h>
#include <m-dict.h>
#include <m-string.h>
#include <m-variant.h>
#include <stdbool.h>
#include <stdlib.h>

VARIANT_DEF2(val, (INT, long long), (REAL, double))
#define M_OPL_val_t() VARIANT_OPLIST(val, M_BASIC_OPLIST, M_BASIC_OPLIST)
DICT_DEF2(val_dict, string_t, val_t)
#define M_OPL_val_dict_t() DICT_OPLIST(val_dict, STRING_OPLIST, M_OPL_val_t())

M_TRY_DEF_ONCE()

struct SeisTraceHeader {
        int rc;
        val_dict_t dict;
        SeisTraceHeaderError err;
};

struct SeisTrace {
        int rc;
        SeisTraceHeader *header;
        double *samples;
        long long samp_num;
};

typedef enum { INT, REAL } SEIS_TRACE_HEADER_VALUE;

SeisTrace *seis_trace_new(long long samp_num) {
        assert(samp_num);
        SeisTrace *t = (SeisTrace *)malloc(sizeof(struct SeisTrace));
        if (!t)
                goto error;
        t->header = seis_trace_header_new();
        if (!t->header)
                goto error;
        t->samples = (double *)malloc(sizeof(double) * samp_num);
        if (!t->samples)
                goto error;
        t->rc = 1;
        t->samp_num = samp_num;
        return t;
error:
        if (t) {
                seis_trace_header_unref(&t->header);
                free(t);
        }
        return NULL;
}

SeisTrace *seis_trace_new_with_header(long long samp_num,
                                      SeisTraceHeader *hdr) {
        assert(samp_num);
        assert(hdr);
        SeisTrace *t = (SeisTrace *)malloc(sizeof(struct SeisTrace));
        if (!t)
                goto error;
        t->samples = (double *)malloc(sizeof(double) * samp_num);
        if (!t->samples)
                goto error;
        t->rc = 1;
        t->header = hdr;
        t->samp_num = samp_num;
        return t;
error:
        seis_trace_header_unref(&hdr);
        if (t) {
                free(t);
        }
        return NULL;
}

SeisTrace *seis_trace_ref(SeisTrace *t) {
        ++t->rc;
        return t;
}

void seis_trace_unref(SeisTrace **t) {
        if (*t)
                if (--(*t)->rc == 0) {
                        free((*t)->samples);
                        seis_trace_header_unref(&(*t)->header);
                        free(*t);
                        *t = NULL;
                }
}

SeisTraceHeader *seis_trace_header_new(void) {
        SeisTraceHeader *hdr =
            (SeisTraceHeader *)malloc(sizeof(struct SeisTraceHeader));
        if (!hdr)
                return NULL;
        M_TRY(exception) { val_dict_init(hdr->dict); }
        M_CATCH(exception, 0) {
                free(hdr);
                return NULL;
        }
        hdr->rc = 1;
        return hdr;
}

SeisTraceHeader *seis_trace_get_header(SeisTrace *trc) { return trc->header; }

SeisTraceHeader const *seis_trace_get_header_const(SeisTrace const *trc) {
        return trc->header;
}

SeisTraceHeader *seis_trace_header_ref(SeisTraceHeader *hdr) {
        ++hdr->rc;
        return hdr;
}

void seis_trace_header_unref(SeisTraceHeader **hdr) {
        if (*hdr)
                if (--(*hdr)->rc == 0) {
                        val_dict_clear((*hdr)->dict);
                        free(*hdr);
                        *hdr = NULL;
                }
}

SeisTraceHeaderErrCode seis_trace_header_set_int(SeisTraceHeader *hdr,
                                                 char const *hdr_name,
                                                 long long val) {
        M_TRY(exception) {
                M_LET(header_name, STRING_OPLIST) {
                        string_set_str(header_name, hdr_name);
                        M_LET(v, M_OPL_val_t()) {
                                val_set_INT(v, val);
                                val_dict_set_at(hdr->dict, header_name, v);
                        }
                }
        }
        M_CATCH(exception, 0) {
                hdr->err.code = SEIS_TRACE_ERR_NO_MEM;
                hdr->err.message =
                    "can not allocate memory in seis_trace_header_set_int";
                return SEIS_TRACE_ERR_NO_MEM;
        }
        return SEIS_TRACE_ERR_OK;
}

SeisTraceHeaderErrCode seis_trace_header_set_real(SeisTraceHeader *hdr,
                                                  char const *hdr_name,
                                                  double val) {
        M_TRY(exception) {
                M_LET(header_name, STRING_OPLIST) {
                        string_set_str(header_name, hdr_name);
                        M_LET(v, M_OPL_val_t()) {
                                val_set_REAL(v, val);
                                val_dict_set_at(hdr->dict, header_name, v);
                        }
                }
        }
        M_CATCH(exception, 0) {
                hdr->err.code = SEIS_TRACE_ERR_NO_MEM;
                hdr->err.message =
                    "can not allocate memory in seis_trace_header_set_real";
                return SEIS_TRACE_ERR_NO_MEM;
        }
        return SEIS_TRACE_ERR_OK;
}

double *seis_trace_get_samples(SeisTrace *t) { return t->samples; }

long long seis_trace_get_samples_num(SeisTrace const *t) { return t->samp_num; }

double const *seis_trace_get_samples_const(SeisTrace const *t) {
        return t->samples;
}

bool seis_trace_header_value_is_int(SeisTraceHeaderValue v) {
        val_t *val = (val_t *)v;
        return val_INT_p(*val);
}

bool seis_trace_header_value_is_real(SeisTraceHeaderValue v) {
        val_t *val = (val_t *)v;
        return val_REAL_p(*val);
}

SeisTraceHeaderValue seis_trace_header_get(SeisTraceHeader *hdr,
                                           char const *hdr_name) {
        val_t *v;
        M_TRY(exception) {
                M_LET(header_name, STRING_OPLIST) {
                        string_set_str(header_name, hdr_name);
                        v = val_dict_get(hdr->dict, header_name);
                }
        }
        M_CATCH(exception, 0) {
                hdr->err.code = SEIS_TRACE_ERR_NO_MEM;
                hdr->err.message =
                    "can not allocate memory in seis_trace_header_get";
                return NULL;
        }
        if (v)
                return v;
        else
                return NULL;
}

long long const *seis_trace_header_value_get_int(SeisTraceHeaderValue v) {
        val_t *val = (val_t *)v;
        return val_get_INT(*val);
}

double const *seis_trace_header_value_get_real(SeisTraceHeaderValue v) {
        val_t *val = (val_t *)v;
        return val_get_REAL(*val);
}

SeisTraceHeaderError const *
seis_trace_header_get_error(SeisTraceHeader const *hdr) {
        return &hdr->err;
}
