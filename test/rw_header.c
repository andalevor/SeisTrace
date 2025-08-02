#include "SeisTrace.h"

#define I_TEST_VALUE 1
#define D_TEST_VALUE 1.0

void set_header(SeisTraceHeader *hdr);
int get_header(SeisTraceHeader *hdr);

int main(void) {
        SeisTraceHeader *hdr = seis_trace_header_new();
        set_header(seis_trace_header_ref(hdr));
        int check = get_header(seis_trace_header_ref(hdr));
        seis_trace_header_unref(&hdr);
        if (check)
                return 1;
}

void set_header(SeisTraceHeader *hdr) {
        seis_trace_header_set_int(hdr, "FFID", I_TEST_VALUE);
        seis_trace_header_set_real(hdr, "CDP_X", D_TEST_VALUE);
        seis_trace_header_set_int(hdr,
                                  "MY VERY VERY LONG INTEGER HEADER NAME"
                                  " TO TEST MEMORY LEAKAGE",
                                  I_TEST_VALUE);
        seis_trace_header_set_real(hdr,
                                   "MY VERY VERY LONG REAL HEADER NAME"
                                   " TO TEST MEMORY LEAKAGE",
                                   D_TEST_VALUE);
        seis_trace_header_unref(&hdr);
}

int get_header(SeisTraceHeader *hdr) {
        SeisTraceHeaderValue v = seis_trace_header_get(hdr, "FFID");
        long long const *ival = seis_trace_header_value_get_int(v);
        if (!ival || *ival != I_TEST_VALUE)
                goto error;
        v = seis_trace_header_get(hdr, "CDP_X");
        double const *rval = seis_trace_header_value_get_real(v);
        if (!rval || *rval != D_TEST_VALUE)
                goto error;
        v = seis_trace_header_get(hdr, "MY VERY VERY LONG INTEGER HEADER NAME"
                                       " TO TEST MEMORY LEAKAGE");
        ival = seis_trace_header_value_get_int(v);
        if (!ival || *ival != I_TEST_VALUE)
                goto error;
        seis_trace_header_unref(&hdr);
        return 0;
error:
        seis_trace_header_unref(&hdr);
        return -1;
}
