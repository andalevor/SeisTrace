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
 * \enum TRACE_HEADER_VALUE
 * \brief Used to set type of header value
 */
typedef enum {INT, REAL} SEIS_TRACE_HEADER_VALUE;

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
 * \fn
 * \brief Could be used to check presence of header value.
 * \param t Pointer to SeisTrace object.
 * \param hdr_name Trace header name to check.
 * \param type Type of header value. Should corresponds to written type.
 * \return Pointer to value or NULL if there no such value.
 */
void *seis_trace_header_find(SeisTrace_t t, char *hdr_name,
							 SEIS_TRACE_HEADER_VALUE type);

/**
 * \fn
 * \brief Gives access to header value or creates it.
 * \param t Pointer to SeisTrace object.
 * \param hdr_name Trace header name to get access.
 * \param type Type of header value. Should corresponds to written type.
 * \return Pointer to value can not be NULL.
 */
void *seis_trace_header_value(SeisTrace_t t, char *hdr_name,
							  SEIS_TRACE_HEADER_VALUE type);

/**
 * \fn seis_trace_get_samples
 * \brief Gets data samples from struct. You should not free memory.
 * \param t SeisTrace object.
 * \param s Pointer to assign samples.
 * \param num Number of samples.
 */
void seis_trace_get_samples(SeisTrace_t t, double **s, long long *num);

#endif /* SEIS_TRACE */
