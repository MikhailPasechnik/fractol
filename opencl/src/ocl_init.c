#include "ocl.h"

cl_device_id	ocl_create_device()
{
	cl_platform_id	platform_id;
	cl_device_id	device_id;
	cl_int			err;

	err = clGetPlatformIDs(1, &platform_id, NULL);
	if (err != CL_SUCCESS)
	{
		OCL_PUT_ERROR(err, "opencl: Couldn't identify a platform");
		return (NULL);
	}
	err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
	if (err != CL_SUCCESS)
		err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);
	if (err != CL_SUCCESS)
	{
		OCL_PUT_ERROR(err, "opencl: No suitable device found");
		return (NULL);
	}
	return (device_id);
}

int				ocl_init(t_ocl *cl)
{
	cl_int	err;
	if (!(cl->device = ocl_create_device()))
		return (0);
	cl->context = clCreateContext(NULL, 1, &cl->device, NULL, NULL, &err);
	if (err != CL_SUCCESS)
	{
		clReleaseDevice(cl->device);
		cl->device = NULL;
		OCL_PUT_ERROR(err, "opencl: Failed to create context");
		return (0);
	}
	cl->queue = clCreateCommandQueueWithProperties(cl->context, cl->device, NULL, &err);
	if (err != CL_SUCCESS)
	{
		clReleaseDevice(cl->device);
		clReleaseContext(cl->context);
		cl->device = NULL;
		cl->context = NULL;
		OCL_PUT_ERROR(err, "opencl: Failed to create queue");
		return (0);
	}
	return (1);
}

