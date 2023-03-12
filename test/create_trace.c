#include "SeisTrace.h"

int main(void)
{
	long long samp_num = 1000;
	SeisTrace *trc = seis_trace_new(samp_num);
	if (!trc)
		return 1;
	seis_trace_unref(trc);
	return 0;
}
