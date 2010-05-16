
// #include <cmath>
// #define __NO_STD_VECTOR // Use cl::vector and cl::string and 
// #define __NO_STD_STRING  // not STL versions, more on this later

#include "clcontext.h"

CLContext* CLContext::Instance () 
{
	static CLContext t;
	return &t;
}

CLContext::CLContext()
{
        devices = NULL;
        maxWorkItemSizes = NULL;
        groupSize = GROUP_SIZE;

	if(setupCL() != CL_SUCCESS)
		exit(1);
}

// API
void CLContext::createBuffer( cl_mem& target, int size, cl_float* floatP, int flags )
{
	cl_int status;
	target = clCreateBuffer( context, flags, size, floatP, &status);
	if (!checkVal( status, CL_SUCCESS, "clCreateBuffer failed. (updatePos)"))
		exit(1);
}

void CLContext::createKernel( cl_kernel& kernel, const char* kname )
{
	cl_int status;
	kernel = clCreateKernel( program, kname, &status);
	if(!checkVal( status, CL_SUCCESS, "clCreateKernel failed."))
		exit(1);
}

void CLContext::setKernelArg( const cl_kernel& kernel, int argnum, int size, void* arg )
{
	cl_int status;
	status = clSetKernelArg( kernel, argnum, size, arg);
	if(!checkVal( status, CL_SUCCESS,  "clSetKernelArg failed. (updatedPos)"))
		exit(1);
}

void CLContext::checkLocalMemsize( const cl_kernel& kernel )
{
	cl_int status;
	cl_ulong usedLocalMemory;           // Used local memory
	status = clGetKernelWorkGroupInfo(kernel, devices[0], CL_KERNEL_LOCAL_MEM_SIZE, sizeof(cl_ulong), &usedLocalMemory, NULL);
	if( !checkVal( status, CL_SUCCESS,  "clGetKernelWorkGroupInfo CL_KERNEL_LOCAL_MEM_SIZE failed." ) )
		exit(1);

	if( usedLocalMemory > totalLocalMemory )
	{
		std::cout << "Unsupported: Insufficient local memory on device." << std::endl;
		exit(1);
	}
}

void CLContext::checkWorkGroupsize( const cl_kernel& kernel )
{
	cl_int status;
	size_t kernelWorkGroupSize;         // Group size returned by kernel

	status = clGetKernelWorkGroupInfo(kernel, devices[0], CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &kernelWorkGroupSize, 0);
	if(!checkVal( status, CL_SUCCESS,  "clGetKernelWorkGroupInfo CL_KERNEL_COMPILE_WORK_GROUP_SIZE failed.")) exit(1);

	if(groupSize > kernelWorkGroupSize)
	{
		std::cout << "Out of Resources!" << std::endl;
		std::cout << "Group Size specified : " << groupSize << std::endl;
		std::cout << "Max Group Size supported on the kernel : " << kernelWorkGroupSize<<std::endl;
		std::cout << "Falling back to " << kernelWorkGroupSize << std::endl;
		groupSize = kernelWorkGroupSize;
	}	
}

void CLContext::enqueueNDRangeKernel( cl_command_queue& command_queue, const cl_kernel& kernel, cl_uint work_dim, const size_t *global_work_offset, const size_t *global_work_size,
					     const size_t *local_work_size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event )
{
	cl_int status;
	status = clEnqueueNDRangeKernel( command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event);
	if(!checkVal( status, CL_SUCCESS,  "clEnqueueNDRangeKernel failed."))
		exit(1);
}

void CLContext::flush( cl_command_queue& command_queue )
{
	cl_int status;
	status = clFlush( commandQueue );
	if(!checkVal( status, CL_SUCCESS,  "clFlush failed."))
		exit(1);
}

void CLContext::finish( cl_command_queue& command_queue )
{
	cl_int status;
	status = clFinish( commandQueue );
	if(!checkVal( status, CL_SUCCESS,  "clFlush failed."))
		exit(1);
}

void CLContext::enqueueReadBuffer( cl_command_queue& command_queue, cl_mem& buffer, cl_bool blocking_read, size_t offset, size_t cb, void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
{
	cl_int status;
	status = clEnqueueReadBuffer( command_queue, buffer, blocking_read, offset, cb, ptr, num_events_in_wait_list, event_wait_list, event);
	if(!checkVal( status, CL_SUCCESS, "clEnqueueReadBuffer failed."))
		exit(1);
}

void CLContext::waitForEvents( cl_uint num_events, const cl_event *event_list )
{
	cl_int status;
	status = clWaitForEvents(num_events, event_list);
	if(!checkVal( status, CL_SUCCESS, "clWaitForEvents failed.")) exit(1);
	clReleaseEvent(events[0]);

}

// SETUP
int CLContext::setupCL()
{
	cl_int status = CL_SUCCESS;

	cl_device_type dType;
	int gpu = 1;

	if(gpu == 0)
		dType = CL_DEVICE_TYPE_CPU;
	else //deviceType = "gpu" 
		dType = CL_DEVICE_TYPE_GPU;

	/*
	* Have a look at the available platforms and pick either
	* the AMD one if available or a reasonable default.      <----- LOL check out the amd propaganda
	*/

	cl_uint numPlatforms;
	cl_platform_id platform = NULL;
	status = clGetPlatformIDs(0, NULL, &numPlatforms);
	if(!checkVal(status, CL_SUCCESS, "clGetPlatformIDs failed."))
		return CL_FAILURE;
	if (0 < numPlatforms) 
	{
		cl_platform_id* platforms = new cl_platform_id[numPlatforms];
		status = clGetPlatformIDs(numPlatforms, platforms, NULL);
		if(!checkVal(status, CL_SUCCESS, "clGetPlatformIDs failed."))
			return CL_FAILURE;
		for (unsigned i = 0; i < numPlatforms; ++i) 
		{
			char pbuf[100];
			status = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, sizeof(pbuf), pbuf, NULL);

			if(!checkVal(status, CL_SUCCESS, "clGetPlatformInfo failed."))
				return CL_FAILURE;

			platform = platforms[i];
			if (!strcmp(pbuf, "Advanced Micro Devices, Inc.")) 
				break;
		}
		delete[] platforms;
	}

	/*
	* If we could find our platform, use it. Otherwise pass a NULL and get whatever the
	* implementation thinks we should be using.
	*/

	cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM,  (cl_context_properties)platform,  0 };
	/* Use NULL for backward compatibility */
	cl_context_properties* cprops = (NULL == platform) ? NULL : cps;

	context = clCreateContextFromType( cprops, dType, NULL, NULL, &status);
	if(!checkVal( status, CL_SUCCESS, "clCreateContextFromType failed."))
		return CL_FAILURE;

	size_t deviceListSize;

	/* First, get the size of device list data */
	status = clGetContextInfo( context,  CL_CONTEXT_DEVICES,  0,  NULL,  &deviceListSize);
	if(!checkVal( status,  CL_SUCCESS, "clGetContextInfo failed."))
		return CL_FAILURE;

	/* Now allocate memory for device list based on the size we got earlier */
	devices = (cl_device_id*)malloc(deviceListSize);
	if(devices==NULL)
	{
		cout << "Failed to allocate memory (devices)." << endl;
		return CL_FAILURE;
	}

	/* Now, get the device list data */
	status = clGetContextInfo( context,  CL_CONTEXT_DEVICES,  deviceListSize,  devices,  NULL);
	if(!checkVal( status, CL_SUCCESS,  "clGetContextInfo failed."))
		return CL_FAILURE;

	/* Create command queue */
	commandQueue = clCreateCommandQueue( context, devices[0], 0, &status);
	if(!checkVal( status, CL_SUCCESS, "clCreateCommandQueue failed."))
		return CL_FAILURE;

	/* Get Device specific Information */
	status = clGetDeviceInfo( devices[0], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), (void*)&maxWorkGroupSize, NULL);

	if(!checkVal( status, CL_SUCCESS,  "clGetDeviceInfo CL_DEVICE_MAX_WORK_GROUP_SIZE failed."))
		return CL_FAILURE;


	status = clGetDeviceInfo( devices[0], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), (void*)&maxDimensions, NULL);
	if(!checkVal( status, CL_SUCCESS,  "clGetDeviceInfo CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS failed."))
		return CL_FAILURE;


	maxWorkItemSizes = (size_t *)malloc(maxDimensions * sizeof(unsigned int));

	status = clGetDeviceInfo( devices[0], CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(size_t) * maxDimensions, (void*)maxWorkItemSizes, NULL);
	if(!checkVal( status, CL_SUCCESS,  "clGetDeviceInfo CL_DEVICE_MAX_WORK_ITEM_SIZES failed."))
		return CL_FAILURE;

	status = clGetDeviceInfo( devices[0], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), (void *)&totalLocalMemory, NULL);
	if(!checkVal( status, CL_SUCCESS,  "clGetDeviceInfo CL_DEVICE_LOCAL_MEM_SIZE failed."))
		return CL_FAILURE;

	/*
	* Create and initialize memory objects
	*/

	/* create a CL program using the kernel source */
	string content;
	fileH.open( "critterding.cl", content ); 

	const char * source = content.c_str();
	size_t sourceSize[] = { strlen(source) };
	program = clCreateProgramWithSource( context, 1, &source, sourceSize, &status);
	if(!checkVal( status, CL_SUCCESS, "clCreateProgramWithSource failed."))
		return CL_FAILURE;

	/* create a cl program executable for all the devices specified */
	status = clBuildProgram( program, 1, &devices[0], NULL, NULL, NULL);
	if(status != CL_SUCCESS)
	{
		if(status == CL_BUILD_PROGRAM_FAILURE)
		{
			cl_int logStatus;
			char * buildLog = NULL;
			size_t buildLogSize = 0;
			logStatus = clGetProgramBuildInfo (program, devices[0], CL_PROGRAM_BUILD_LOG, buildLogSize, buildLog, &buildLogSize);
			if(!checkVal( logStatus, CL_SUCCESS, "clGetProgramBuildInfo failed."))
				return CL_FAILURE;

			buildLog = (char*)malloc(buildLogSize);
			if(buildLog == NULL)
			{
				cout << "Failed to allocate host memory. (buildLog)" << endl;
				return CL_FAILURE;
			}
			memset(buildLog, 0, buildLogSize);

			logStatus = clGetProgramBuildInfo (program, devices[0], CL_PROGRAM_BUILD_LOG, buildLogSize, buildLog, NULL);
			if(!checkVal( logStatus, CL_SUCCESS, "clGetProgramBuildInfo failed."))
			{
				free(buildLog);
				return CL_FAILURE;
			}

			std::cout << " \n\t\t\tBUILD LOG\n";
			std::cout << " ************************************************\n";
			std::cout << buildLog << std::endl;
			std::cout << " ************************************************\n";
			free(buildLog);
		}

		if(!checkVal( status, CL_SUCCESS, "clBuildProgram failed."))
			return CL_FAILURE;
	}

	return CL_SUCCESS;
}

template<typename T>
int CLContext::checkVal( T input, T reference, std::string message, bool isAPIerror) const
{
	if( input==reference )
		return 1;
	else
	{
		if( isAPIerror )
		{
			cerr << "Error: "<< message << " Error code : ";
			cerr << getOpenCLErrorCodeStr(input) << endl;
		}
		else
			cout << message << endl;   
		return 0;
	}
}

const char* CLContext::getOpenCLErrorCodeStr(std::string input) const
{
    return "unknown error code"; 
}

template<typename T>
const char*  CLContext::getOpenCLErrorCodeStr(T input) const
{
	int errorCode = (int)input;
	switch(errorCode)
	{
		case CL_DEVICE_NOT_FOUND:			return "CL_DEVICE_NOT_FOUND";
		case CL_DEVICE_NOT_AVAILABLE:			return "CL_DEVICE_NOT_AVAILABLE";               
		case CL_COMPILER_NOT_AVAILABLE:			return "CL_COMPILER_NOT_AVAILABLE";           
		case CL_MEM_OBJECT_ALLOCATION_FAILURE:		return "CL_MEM_OBJECT_ALLOCATION_FAILURE";      
		case CL_OUT_OF_RESOURCES:			return "CL_OUT_OF_RESOURCES";                    
		case CL_OUT_OF_HOST_MEMORY:			return "CL_OUT_OF_HOST_MEMORY";                 
		case CL_PROFILING_INFO_NOT_AVAILABLE:		return "CL_PROFILING_INFO_NOT_AVAILABLE";
		case CL_MEM_COPY_OVERLAP:			return "CL_MEM_COPY_OVERLAP";                    
		case CL_IMAGE_FORMAT_MISMATCH:			return "CL_IMAGE_FORMAT_MISMATCH";               
		case CL_IMAGE_FORMAT_NOT_SUPPORTED:		return "CL_IMAGE_FORMAT_NOT_SUPPORTED";         
		case CL_BUILD_PROGRAM_FAILURE:			return "CL_BUILD_PROGRAM_FAILURE";              
		case CL_MAP_FAILURE:				return "CL_MAP_FAILURE";                         
		case CL_INVALID_VALUE:				return "CL_INVALID_VALUE";                      
		case CL_INVALID_DEVICE_TYPE:			return "CL_INVALID_DEVICE_TYPE";               
		case CL_INVALID_PLATFORM:			return "CL_INVALID_PLATFORM";                   
		case CL_INVALID_DEVICE:				return "CL_INVALID_DEVICE";                    
		case CL_INVALID_CONTEXT:			return "CL_INVALID_CONTEXT";                    
		case CL_INVALID_QUEUE_PROPERTIES:		return "CL_INVALID_QUEUE_PROPERTIES";           
		case CL_INVALID_COMMAND_QUEUE:			return "CL_INVALID_COMMAND_QUEUE";              
		case CL_INVALID_HOST_PTR:			return "CL_INVALID_HOST_PTR";                   
		case CL_INVALID_MEM_OBJECT:			return "CL_INVALID_MEM_OBJECT";                  
		case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:	return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";    
		case CL_INVALID_IMAGE_SIZE:			return "CL_INVALID_IMAGE_SIZE";                 
		case CL_INVALID_SAMPLER:			return "CL_INVALID_SAMPLER";                    
		case CL_INVALID_BINARY:				return "CL_INVALID_BINARY";                     
		case CL_INVALID_BUILD_OPTIONS:			return "CL_INVALID_BUILD_OPTIONS";              
		case CL_INVALID_PROGRAM:			return "CL_INVALID_PROGRAM";                    
		case CL_INVALID_PROGRAM_EXECUTABLE:		return "CL_INVALID_PROGRAM_EXECUTABLE";          
		case CL_INVALID_KERNEL_NAME:			return "CL_INVALID_KERNEL_NAME";                
		case CL_INVALID_KERNEL_DEFINITION:		return "CL_INVALID_KERNEL_DEFINITION";          
		case CL_INVALID_KERNEL:				return "CL_INVALID_KERNEL";                     
		case CL_INVALID_ARG_INDEX:			return "CL_INVALID_ARG_INDEX";                   
		case CL_INVALID_ARG_VALUE:			return "CL_INVALID_ARG_VALUE";                   
		case CL_INVALID_ARG_SIZE:			return "CL_INVALID_ARG_SIZE";                    
		case CL_INVALID_KERNEL_ARGS:			return "CL_INVALID_KERNEL_ARGS";                
		case CL_INVALID_WORK_DIMENSION:			return "CL_INVALID_WORK_DIMENSION";              
		case CL_INVALID_WORK_GROUP_SIZE:		return "CL_INVALID_WORK_GROUP_SIZE";             
		case CL_INVALID_WORK_ITEM_SIZE:			return "CL_INVALID_WORK_ITEM_SIZE";             
		case CL_INVALID_GLOBAL_OFFSET:			return "CL_INVALID_GLOBAL_OFFSET";              
		case CL_INVALID_EVENT_WAIT_LIST:		return "CL_INVALID_EVENT_WAIT_LIST";             
		case CL_INVALID_EVENT:				return "CL_INVALID_EVENT";                      
		case CL_INVALID_OPERATION:			return "CL_INVALID_OPERATION";                 
		case CL_INVALID_GL_OBJECT:			return "CL_INVALID_GL_OBJECT";                  
		case CL_INVALID_BUFFER_SIZE:			return "CL_INVALID_BUFFER_SIZE";                 
		case CL_INVALID_MIP_LEVEL:			return "CL_INVALID_MIP_LEVEL";                   
		case CL_INVALID_GLOBAL_WORK_SIZE:		return "CL_INVALID_GLOBAL_WORK_SIZE";            
		default:					return "unknown error code";
	}
	return "unknown error code";
}

CLContext::~CLContext()
{
    clReleaseProgram(program);
    clReleaseCommandQueue(commandQueue);
    clReleaseContext(context);

    if(devices)
        free(devices);

    if(maxWorkItemSizes)
        free(maxWorkItemSizes);
}

/////////////////////////////////////////////////////////////////
// Template Instantiations 
/////////////////////////////////////////////////////////////////
template
int CLContext::checkVal<char>(char input, char reference, std::string message, bool isAPIerror) const;
template
int CLContext::checkVal<std::string>(std::string input, std::string reference, std::string message, bool isAPIerror) const;
template
int CLContext::checkVal<short>(short input, short reference, std::string message, bool isAPIerror) const;
template
int CLContext::checkVal<unsigned int>(unsigned int  input, unsigned int  reference, std::string message, bool isAPIerror) const;
template
int CLContext::checkVal<int>(int input, int reference, std::string message, bool isAPIerror) const;

template
const char* CLContext::getOpenCLErrorCodeStr(int input) const;
