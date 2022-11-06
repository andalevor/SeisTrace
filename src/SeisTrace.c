#include <m-dict.h>
#include <m-string.h>
#include <m-variant.h>
#include <stdlib.h>
#include "SeisTrace.h"

VARIANT_DEF2(val, (INT, long long), (REAL, double))
#define M_OPL_val_t() VARIANT_OPLIST(val, M_BASIC_OPLIST, M_BASIC_OPLIST)
DICT_DEF2(val_dict, string_t, val_t)
#define M_OPL_val_dict_t() DICT_OPLIST(val_dict, STRING_OPLIST, M_OPL_val_t())

struct SeisTrace {
	int rc;
	val_dict_t header;
	double *samples;
	long long samp_num;
};

typedef enum {INT, REAL} SEIS_TRACE_HEADER_VALUE;

SeisTrace_t seis_trace_new(long long samp_num)
{
	SeisTrace_t t = (SeisTrace_t)malloc(sizeof(struct SeisTrace));
	t->rc = 1;
	val_dict_init(t->header);
	t->samples = (double *)malloc(sizeof(double) * samp_num);
	t->samp_num = samp_num;
	return t;
}

SeisTrace_t seis_trace_ref(SeisTrace_t t)
{
	++t->rc;
	return t;
}

void seis_trace_unref(SeisTrace_t t)
{
	if (--t->rc == 0) {
		free(t->samples);
		val_dict_clear(t->header);
		free(t);
	}
}

void seis_trace_header_set_int(SeisTrace_t t, char *hdr_name, long long val)
{
	string_t header_name;
	string_init_set_str(header_name, hdr_name);
	val_t v;
	val_init(v);
	val_set_INT(v, val);
	val_dict_set_at(t->header, header_name, v);
}

void seis_trace_header_set_real(SeisTrace_t t, char *hdr_name, double val)
{
	string_t header_name;
	string_init_set_str(header_name, hdr_name);
	val_t v;
	val_init(v);
	val_set_REAL(v, val);
	val_dict_set_at(t->header, header_name, v);
}

long long *seis_trace_header_get_int(SeisTrace_t t, char *hdr_name)
{
	string_t header_name;
	string_init_set_str(header_name, hdr_name);
	val_t *v = val_dict_get(t->header, header_name);
	if (v)
		return val_get_INT(*v);
	else
		return NULL;
}

double *seis_trace_header_get_real(SeisTrace_t t, char *hdr_name)
{
	string_t header_name;
	string_init_set_str(header_name, hdr_name);
	val_t *v = val_dict_get(t->header, header_name);
	if (v)
		return val_get_REAL(*v);
	else
		return NULL;
}

void seis_trace_get_samples(SeisTrace_t t, double **s, long long *num)
{
	*s = t->samples;
	*num = t->samp_num;
}
