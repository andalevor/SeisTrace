#include "SeisTrace.h"

void write_samp(SeisTrace *trc);
int read_samp(SeisTrace const *trc);

int main(void)
{
	long long samp_num = 1000;
	SeisTrace *trc = seis_trace_new(samp_num);
	write_samp(seis_trace_ref(trc));
	int check = read_samp(seis_trace_ref(trc));
	if (check)
		return 1;
	seis_trace_unref(trc);
}

void write_samp(SeisTrace *trc)
{
	long long samp_num = seis_trace_get_samples_num(trc);
	double *samples = seis_trace_get_samples(trc);
	for (long long i = 0; i < samp_num; ++i)
		samples[i] = i;
	seis_trace_unref(trc);
}

int read_samp(SeisTrace const *trc)
{
	long long samp_num = seis_trace_get_samples_num(trc);
	double const *samples = seis_trace_get_samples_const(trc);
	for (long long i = 0; i < samp_num; ++i)
		if (samples[i] != i)
			goto error;
	seis_trace_unref((SeisTrace*)trc);
	return 0;
error:
	seis_trace_unref((SeisTrace*)trc);
	return -1;
}
