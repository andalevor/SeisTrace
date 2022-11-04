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

void *seis_trace_header_value(SeisTrace_t t, char *hdr_name,
							  SEIS_TRACE_HEADER_VALUE type)
{
	string_t header_name;
	string_init(header_name);
	string_set_str(header_name, hdr_name);
	val_t *result = val_dict_get(t->header, header_name);
	if (type == INT)
		return (void *)val_get_INT(*result);
	else if (type == REAL)
		return (void *)val_get_REAL(*result);
	else abort();
}

void seis_trace_get_samples(SeisTrace_t t, double **s, long long *num)
{
	*s = t->samples;
	*num = t->samp_num;
}
