#include "SeisTrace.h"

#define I_TEST_VALUE 1
#define D_TEST_VALUE 1.0

void set_header(SeisTraceHeader *hdr);
int get_header(SeisTraceHeader const *hdr);

int main(void)
{
	SeisTraceHeader *hdr = seis_trace_header_new();
	set_header(seis_trace_header_ref(hdr));
	int check = get_header(seis_trace_header_ref(hdr));
	if (check)
		return 1;
	seis_trace_header_unref(hdr);
}

void set_header(SeisTraceHeader *hdr)
{
	seis_trace_header_set_int(hdr, "FFID", I_TEST_VALUE);
	seis_trace_header_set_real(hdr, "CDP_X", D_TEST_VALUE);
	/** seis_trace_header_set_int(hdr, "MY VERY VERY LONG INTEGER HEADER NAME" */
	/**                           " TO TEST MEMORY LEAKAGE", I_TEST_VALUE); */
	/** seis_trace_header_set_real(hdr, "MY VERY VERY LONG REAL HEADER NAME" */
	/**                           " TO TEST MEMORY LEAKAGE", D_TEST_VALUE); */
	seis_trace_header_unref(hdr);
}

int get_header(SeisTraceHeader const *hdr)
{
	long long const *ival = seis_trace_header_get_int(hdr, "FFID");
	if (!ival || *ival != I_TEST_VALUE)
		goto error;
	double const *rval = seis_trace_header_get_real(hdr, "CDP_X");
	if (!rval || *rval != D_TEST_VALUE)
		goto error;
	/** ival = seis_trace_header_get_int(hdr, "MY VERY VERY LONG " */
	/**                                  "INTEGER HEADER NAME"); */
	/** if (!ival || *ival != I_TEST_VALUE) */
	/**     goto error; */
	/** rval = seis_trace_header_get_real(hdr, "MY VERY VERY LONG " */
	/**                                   "REAL HEADER NAME"); */
	/** if (!rval || *rval != D_TEST_VALUE) */
	/**     goto error; */
	seis_trace_header_unref((SeisTraceHeader*)hdr);
	return 0;
error:
	seis_trace_header_unref((SeisTraceHeader*)hdr);
	return -1;
}
