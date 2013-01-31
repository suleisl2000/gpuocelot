#ifndef LCL_RUNTIME_H_INCLUDED
#define LCL_RUNTIME_H_INCLUDED

#include <ocelot/opencl/interface/opencl_runtime.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LCL_INVALID_VIRTUAL_BUFFER -99

typedef struct _lcl_vbuf * lcl_vbuf;
typedef cl_context lcl_context;
typedef cl_command_queue lcl_command_queue;
typedef cl_event lcl_event;


typedef cl_int lcl_int;
typedef cl_uint lcl_uint;
typedef cl_bool lcl_bool;

extern lcl_vbuf lclCreateVirtualBuffer(lcl_context context,
							  size_t size,
							  lcl_int * errcode_ret);

extern lcl_int lclWriteVirtualBuffer(lcl_command_queue command_queue,
					lcl_vbuf virtual_buffer,
					lcl_bool blocking_write,
					size_t offset,
					size_t cb,
					const void * ptr,
					lcl_uint num_events_in_wait_list,
					const lcl_event * event_wait_list,
					lcl_event * event);

#ifdef __cplusplus
}
#endif

#endif
