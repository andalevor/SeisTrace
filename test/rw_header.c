#include "SeisTrace.h"

void set_header(SeisTraceHeader_t hdr);
int get_header(SeisTraceHeader_t hdr);

int main(void)
{
	SeisTraceHeader_t hdr = seis_trace_header_new();
	set_header(seis_trace_header_ref(hdr));
	int check = get_header(seis_trace_header_ref(hdr));
	if (check)
		return 1;
	seis_trace_header_unref(hdr);
}

void set_header(SeisTraceHeader_t hdr)
{
	seis_trace_header_set_int(hdr, "FFID", 1);
	seis_trace_header_set_real(hdr, "CDP_X", 1.0);
	seis_trace_header_unref(hdr);
}

int get_header(SeisTraceHeader_t hdr)
{
	long long *ival = seis_trace_header_get_int(hdr, "FFID");
	if (!ival || *ival != 1)
		goto error;
	double *rval = seis_trace_header_get_real(hdr, "CDP_X");
	if (!rval || *rval != 1.0)
		goto error;
	seis_trace_header_unref(hdr);
	return 0;
error:
	seis_trace_header_unref(hdr);
	return -1;
}
