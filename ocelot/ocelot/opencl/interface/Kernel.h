#ifndef OCELOT_OPENCL_KERNEL_H_INCLUDED
#define OCELOT_OPENCL_KERNEL_H_INCLUDED

// C++ libs
#include <string>
#include <map>
#include <set>

// Ocelot libs
#include <ocelot/opencl/interface/OpenCLRuntimeInterface.h>
#include <ocelot/opencl/interface/Program.h>
#include <ocelot/opencl/interface/Context.h>
#include <ocelot/opencl/interface/Object.h>

namespace opencl {

	class Program;
 
	typedef std::map< unsigned int, size_t > SizeMap;
   	typedef std::map<unsigned int, char * > PointerMap;
	typedef std::map< unsigned int, unsigned int > OffsetMap;

   
    //! references a kernel registered to OpenCL runtime
	class Kernel : public Object{

	public:
		Kernel(const std::string& name, Program * program);
		~Kernel();

	public:
		void release();

		//validate context
		bool isValidContext(Context * context);

		//add device info
		void addDeviceInfo(Device * device, std::string moduleName, 
				ir::Module * module, ir::Kernel * irKernel);

		//Set arguments
		void setArg(cl_uint arg_index, size_t arg_size, const void * arg_value);

		//Map parameters
		void mapParametersOnDevice(Device * device);

		//Set kernel configuration
		void setConfiguration(cl_uint work_dim, const size_t * global_work_offset,
        	const size_t * global_work_size, const size_t * local_work_size);

		//Launch kernel
		void launchOnDevice(Device * device);

	private:
		//! name of kernel
		const std::string _name;

		//! associated program
		Program * _program;

		//! device info
		typedef struct {
			//module name
			std::string _moduleName;

			//ir module
			ir::Module * _module;

			//ir kernel
			ir::Kernel * _irKernel;
		}deviceInfoT;

		std::map< Device *, deviceInfoT > _deviceInfo;

		//! Sizes for individual parameter
		SizeMap _parameterSizes;
		
		//! Sizes for individual parameters
		PointerMap _parameterPointers;

		//! parameter memory
		char * _parameterBlock;
		
		//! size of parameter memory
		size_t _parameterBlockSize;

		//! offset of parameters
		OffsetMap _parameterOffsets;	

		//! number of dimensions for work-items
		cl_uint _workDim;
		
		//! global ID offset for work-items
		size_t _globalWorkOffset[3];

		//! global dimensions of work-items
		size_t _globalWorkSize[3];

		//! local dimensions of work-items in work-group
		size_t _localWorkSize[3];

		//! number of work groups
		size_t _workGroupNum[3];

	private:
		//! check if built on device
		bool _isBuiltOnDevice(Device * device);
			
	};
	

}

#endif
