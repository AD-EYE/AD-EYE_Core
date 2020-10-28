#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "cuda.h"

int main()
{
    size_t free_byte ;
    size_t total_byte ;
    int device ;
    int nDevices;
    cudaDeviceProp prop;

    // Get and print GPU information for all precent devices
    cudaGetDeviceCount(&nDevices);
	for (int i = 0; i < nDevices; i++) {
            cudaGetDeviceProperties(&prop, i);
            std::cout << "\nDevice Number: " << i << "\nDevice name: " << prop.name << "\nMemory Clock Rate (KHz): " << prop.memoryClockRate << "\nMemory Bus Width (bits): " << "\nMemory Size (MB): " << prop.totalGlobalMem/1000000 << prop.memoryBusWidth << "\nPeak Memory Bandwidth (GB/s): " << 2.0*prop.memoryClockRate*(prop.memoryBusWidth/8)/1.0e6 << "\n" << std::endl;
	}
 
    std::cout << "\n" << std::endl;

    while (true)
    {
        cudaError_t cuda_status = cudaMemGetInfo( &free_byte, &total_byte ) ;
	
        if ( cudaSuccess != cuda_status ){
            std::cout << "Error: cudaMemGetInfo fails, " << cudaGetErrorString(cuda_status) << std::endl;
            exit(1);
        }
        
        //Get the currently used GPU device ID
	    cuda_status = cudaGetDevice( &device );

	    if ( cudaSuccess != cuda_status ){
            std::cout << "Error: cudaGetDevice fails, " << cudaGetErrorString(cuda_status) << std::endl;
            exit(1);
        }

        //Calculate the memory usage
        double free_db = (double)free_byte ;
        double total_db = (double)total_byte ;
        double used_db = total_db - free_db ;
    
        //Set the decimal precision
        std::cout << std::fixed;
	    std::cout << std::setprecision(2); // 2 = 2 decimal points
        
        //Print the GPU id and Memory usage in percentage
        std::cout << "GPU STATS FOR DEVICE " << device << std::endl;	
	    std::cout << "Memory used: " << (used_db/total_db)*100 << " %\n" << std::endl;
        
        //Sleep 1 second befor sampling again 
        sleep(1);
    }

    //return 0;
}
