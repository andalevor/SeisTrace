/**
 * \file SeisTrace.h
 * \brief Main type and functions declarations.
 * \author andalevor
 * \date 2022/10/31
 */

#ifndef SEIS_TRACE
#define SEIS_TRACE

/**
 * \struct SeisTrace
 * \brief Main type for seismic trace.
 */
typedef struct SeisTrace *SeisTrace_t;

/**
 * \fn seis_trace_new
 * \brief Creates new SeisTrace object.
 * \param samp_num Number of samples in created trace.
 * \return Pointer to SeisTrace.
 */
SeisTrace_t seis_trace_new(long long samp_num);

/**
 * \fn seis_trace_ref
 * \brief Makes rc increment.
 * \param t Pointer to SeisTrace object.
 * \return Pointer to SeisTrace object.
 */
SeisTrace_t seis_trace_ref(SeisTrace_t t);

/**
 * \fn seis_trace_unref
 * \brief Frees memory.
 * \param t Pointer to SeisTrace object.
 */
void seis_trace_unref(SeisTrace_t t);

/**
 * \fn seis_trace_header_set_int
 * \brief Sets integer trace header value.
 * \param t Pointer to SeisTrace object.
 * \param hdr_name Trace header name to set value.
 * \param val Value to set.
 */
void seis_trace_header_set_int(SeisTrace_t t, char *hdr_name, long long val);

/**
 * \fn seis_trace_header_set_real
 * \brief Sets real trace header value.
 * \param t Pointer to SeisTrace object.
 * \param hdr_name Trace header name to set value.
 * \param val Value to set.
 */
void seis_trace_header_set_real(SeisTrace_t t, char *hdr_name, double val);

/**
 * \fn seis_trace_header_get_int
 * \brief Gets trace header value.
 * \param t Pointer to SeisTrace object.
 * \param hdr_name Trace header name to get value.
 * \return Pointer to trace header value or NULL if no such header name.
 */
long long *seis_trace_header_get_int(SeisTrace_t t, char *hdr_name);

/**
 * \fn seis_trace_header_get_real
 * \brief Gets trace header value.
 * \param t Pointer to SeisTrace object.
 * \param hdr_name Trace header name to get value.
 * \return Trace header value.
 */
double *seis_trace_header_get_real(SeisTrace_t t, char *hdr_name);

/**
 * \fn seis_trace_get_samples
 * \brief Gets data samples from struct. You should not free memory.
 * \param t SeisTrace object.
 * \param s Pointer to assign samples.
 * \param num Number of samples.
 */
void seis_trace_get_samples(SeisTrace_t t, double **s, long long *num);

#endif /* SEIS_TRACE */
