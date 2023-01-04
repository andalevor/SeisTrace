#include "SeisTrace.h"

int main(void)
{
	SeisTraceHeader_t hdr = seis_trace_header_new();
	seis_trace_header_set_int(hdr, "FFID", 1);
	seis_trace_header_set_real(hdr, "CDP_X", 1.0);
	long long samp_num = 1000;
	SeisTrace_t trc = seis_trace_new_with_header(samp_num, hdr);
	seis_trace_unref(trc);
}
