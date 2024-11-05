#include "SeisTrace.h"

int main(void) {
        SeisTraceHeader *hdr = seis_trace_header_new();
        if (!hdr)
                return 1;
        seis_trace_header_unref(&hdr);
        return 0;
}
