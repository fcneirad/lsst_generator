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

	int mpd_bins = 200;

	std::string json_input_filename = argv[1];

	// Set the generic parameters
	genericParameters gen(json_input_filename);

	// Set the velocities (here only Dls, Dl and Ds are needed), no velocities are drawn from the distributions
	velocityParameters vp(json_input_filename);

	// Map loop
	for(int ii=0;ii<gen.ids.size();ii++){
		double Rein = 13.5*sqrt(gen.mass[ii]*vp.Dls*vp.Ds/vp.Dl); // in 10^14 cm
		MagnificationMap map(gen.ids[ii],Rein);

		// Set the profiles for convolution
		std::vector<BaseProfile*> profiles = createProfilesFromInput(json_input_filename,map.pixSizePhys);

		// Set convolution kernel
		int profMaxOffset = (int) ceil(profiles[gen.lrest.size()-1]->Nx/2);
		EffectiveMap emap(profMaxOffset,&map);
		Kernel kernel(map.Nx,map.Ny);

		int rows = mpd_bins;
		int cols = gen.lrest.size()+1;
		double all_mpds[rows][cols];

		//std::string* path_2_write = (std::string*)malloc((gen.lrest.size())*strlen(gen.path_2_output+"convolved_map_99.fits") + 1);
		for(int j=0;j<gen.lrest.size();j++){
			kernel.setKernel(profiles[j]);
			map.convolve(&kernel,&emap);

			Mpd c = emap.getBinnedMpd(mpd_bins);

			// assign c.bins to the first column of the array to be saved
			// assign c.counts to the rest of the columns
			for(int r=0; r<mpd_bins; r++){
				if(j == 0){
					all_mpds[r][0] = c.bins[r];
				}
				all_mpds[r][j+1] = c.counts[r];
			}

		}
		std::string path_2_write = gen.path_2_output+gen.ids[ii]+".dat";
		FILE* fh = fopen(path_2_write.data(),"w");
		for(int r=0; r<mpd_bins; r++){
			for(int c=0; c<gen.lrest.size()+1; c++){
				fprintf(fh, "%11.6e ", all_mpds[r][c]);
			}
			fprintf(fh, "\n");
		}
		fclose(fh);
		std::cout << "map " << ii+1 << "/" << gen.ids.size() << " done" << std::endl;
	}

	std::cout << "Done." << std::endl;
	return 0;
}
