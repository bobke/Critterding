#ifndef CLCONTEXT_H
#define CLCONTEXT_H

#define CL_SUCCESS 0
#define CL_FAILURE 1
// #define CL_EXPECTED_FAILURE 2

#ifdef OSX
	#include <OpenCL/cl.h>
#else
	#include <CL/cl.hpp>
// 	#include <CL/cl.h>
#endif
#include <utility>
#include <malloc.h>

#define GROUP_SIZE 256
#include "../utils/file.h"

#include <iostream>
using namespace std;

class CLContext
{
	public:
		static CLContext* Instance();
		~CLContext();

		void createBuffer( cl_mem& target, int size, cl_float* floatP, int flags );
		void createKernel( cl_kernel& kernel, const char* kname );
		void setKernelArg( const cl_kernel& kernel, int argnum, int size, void* arg );
		void checkLocalMemsize( const cl_kernel& kernel );
		void checkWorkGroupsize( const cl_kernel& kernel );
		void enqueueNDRangeKernel( cl_command_queue& command_queue, const cl_kernel& kernel, cl_uint work_dim, const size_t *global_work_offset, const size_t *global_work_size,
					     const size_t *local_work_size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event );
		void flush( cl_command_queue& command_queue );
		void finish( cl_command_queue& command_queue );
		void enqueueReadBuffer( cl_command_queue& command_queue, cl_mem& buffer, cl_bool blocking_read, size_t offset, size_t cb, void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event );
		void waitForEvents( cl_uint num_events, const cl_event *event_list );
		

		size_t groupSize;                   /**< Work-Group size */
		cl_context context;                 /**< CL context */
		cl_device_id *devices;              /**< CL device list */
		cl_command_queue commandQueue;      /**< CL command queue */
		size_t maxWorkGroupSize;            /**< Max allowed work-items in a group */
		cl_uint maxDimensions;              /**< Max group dimensions allowed */
		size_t * maxWorkItemSizes;           /**< Max work-items sizes in each dimensions */
		cl_ulong totalLocalMemory;          /**< Max local memory allowed */
		cl_program program;                 /**< CL program */

		const char* getOpenCLErrorCodeStr(std::string input) const;
		template<typename T>
		const char* getOpenCLErrorCodeStr(T input) const;

		template<typename T> 
		int checkVal( T input, T reference, std::string message, bool isAPIerror = true) const;

		cl_event events[1];
	protected:
		CLContext();
	private:
		File fileH;
		int setupCL();

		inline void checkErr(cl_int err, const char * name) {
			if (err != CL_SUCCESS) {
				cout<< "ERROR: " << name << " (" << err << ")" << std::endl;
				exit(EXIT_FAILURE);
			}
		}

};


#endif
