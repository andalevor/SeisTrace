/**
 * \file SeisTrace.h
 * \brief Main type and functions declarations.
 * \author andalevor
 * \date 2022/10/31
 */

#ifndef SEIS_TRACE_H
#define SEIS_TRACE_H

/**
 * \struct SeisTrace
 * \brief Main type for seismic trace.
 */
typedef struct SeisTrace *SeisTrace_t;

/**
 * \struct SeisTraceHeader
 * \brief Type for seismic trace header
 */
typedef struct SeisTraceHeader *SeisTraceHeader_t;

/**
 * \fn seis_trace_new
 * \brief Creates new SeisTrace object.
 * \param samp_num Number of samples in created trace. Can not be zero.
 * \return Pointer to SeisTrace or NULL if there are no free memory.
 */
SeisTrace_t seis_trace_new(long long samp_num);

/**
 * \fn seis_trace_new
 * \brief Creates new SeisTrace object.
 * \param samp_num Number of samples in created trace.
 * \param hdr SeisTraceHeader object. Trace will own header.
 * \return Pointer to SeisTrace or NULL if there are no free memory.
 */
SeisTrace_t seis_trace_new_with_header(long long samp_num, SeisTraceHeader_t hdr);

/**
 * \fn seis_trace_ref
 * \brief Makes rc increment.
 * \param t Pointer to SeisTrace object.
 * \return Pointer to SeisTrace object.
 */
SeisTrace_t seis_trace_ref(SeisTrace_t trc);

/**
 * \fn seis_trace_unref
 * \brief Rc decrement. Frees memory when rc = 0.
 * \param t Pointer to SeisTrace object.
 */
void seis_trace_unref(SeisTrace_t trc);

/**
 * \fn seis_trace_get_header
 * \brief Gets trace header.
 * It's a part of trace. And should not be fried.
 * \param t Pointer to SeisTrace object.
 */
SeisTraceHeader_t seis_trace_get_header(SeisTrace_t trc);

/**
 * \fn seis_trace_get_samples
 * \brief Gets data samples from struct. You should not free memory.
 * \param t SeisTrace object.
 */
double *seis_trace_get_samples(SeisTrace_t trc);

/**
 * \fn seis_trace_get_samples_num
 * \brief Gets data samples number from struct.
 * \param t SeisTrace object.
 */
long long seis_trace_get_samples_num(SeisTrace_t trc);

/**
 * \fn seis_trace_header_new
 * \brief Creates new SeisTraceHeader object.
 * \return Pointer to SeisTraceHeader or NULL if there are no free memory.
 */
SeisTraceHeader_t seis_trace_header_new(void);

/**
 * \fn seis_trace_header_ref
 * \brief Makes rc increment.
 * \param t Pointer to SeisTraceHeader object.
 * \return Pointer to SeisTraceHeader object.
 */
SeisTraceHeader_t seis_trace_header_ref(SeisTraceHeader_t trc);

/**
 * \fn seis_trace_header_unref
 * \brief Rc decrement. Frees memory when rc = 0.
 * \param t Pointer to SeisTraceHeader object.
 */
void seis_trace_header_unref(SeisTraceHeader_t trc);

/**
 * \fn seis_trace_header_set_int
 * \brief Sets integer trace header value.
 * \param t Pointer to SeisTraceHeader object.
 * \param hdr_name Trace header name to set value.
 * \param val Value to set.
 */
void seis_trace_header_set_int(SeisTraceHeader_t hdr, char *hdr_name,
							   long long val);

/**
 * \fn seis_trace_header_set_real
 * \brief Sets real trace header value.
 * \param t Pointer to SeisTraceHeader object.
 * \param hdr_name Trace header name to set value.
 * \param val Value to set.
 */
void seis_trace_header_set_real(SeisTraceHeader_t hdr, char *hdr_name,
							   	double val);

/**
 * \fn seis_trace_header_get_int
 * \brief Gets trace header value.
 * \param t Pointer to SeisTraceHeader object.
 * \param hdr_name Trace header name to get value.
 * \return Pointer to trace header value or NULL if no such header name.
 */
long long *seis_trace_header_get_int(SeisTraceHeader_t hdr, char *hdr_name);

/**
 * \fn seis_trace_header_get_real
 * \brief Gets trace header value.
 * \param t Pointer to SeisTraceHeader object.
 * \param hdr_name Trace header name to get value.
 * \return Trace header value.
 */
double *seis_trace_header_get_real(SeisTraceHeader_t hdr, char *hdr_name);

#endif /* SEIS_TRACE_H */
