#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <fstream>
#include <cstring>

#include "json/json.h"

#include "gerlumph.hpp"
#include "auxiliary_functions.hpp"


int main(int argc, char* argv[]){
	if( argc != 2 ){
		std::cout << "1 command line argument is required!" << std::endl;
		std::cout << "1st: the path to the json file containing all the parameters for the run." << std::endl;
		return 0;
	}

	std::string json_input_filename = argv[1];

	// Set the generic parameters
	genericParameters gen(json_input_filename);

	// Set the velocities (here only Dls, Dl and Ds are needed), no velocities are drawn from the distributions
	velocityParameters vp(json_input_filename);

	// Map loop
	for(int ii=0;ii<gen.ids.size();ii++){
		double Rein = 13.5*sqrt(gen.mass[ii]*vp.Dls*vp.Ds/vp.Dl); // in 10^14 cm
		std::cout << "Rein is: " << Rein << " x10^14 cm" << std::endl;
		MagnificationMap map(gen.ids[ii],Rein);

		// Set the profiles for convolution
		std::vector<BaseProfile*> profiles = createProfilesFromInput(json_input_filename,map.pixSizePhys);

		// Set convolution kernel
		int profMaxOffset = (int) ceil(profiles[gen.lrest.size()-1]->Nx/2);
		EffectiveMap emap(profMaxOffset,&map);
		Kernel kernel(map.Nx,map.Ny);

		std::cout << "starting convolutions" << std::endl;
		//std::string* path_2_write = (std::string*)malloc((gen.lrest.size())*strlen(gen.path_2_output+"convolved_map_99.fits") + 1);
		for(int j=0;j<gen.lrest.size();j++){
			kernel.setKernel(profiles[j]);
			map.convolve(&kernel,&emap);

			//path_2_write[j] = gen.path_2_output+"convolved_map_"+std::to_string(j)+".fits";
			std::string path_2_write = gen.path_2_output+"convolved_map_"+std::to_string(j)+".fits";
			emap.writeImageFITS(path_2_write, 1);
			std::cout << "convolution " << j+1 << "/" << gen.lrest.size() << " done" << std::endl;
		}

	}

	std::cout << "Done." << std::endl;
	return 0;
}
