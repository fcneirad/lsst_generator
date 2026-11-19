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

		Mpd c = map.getBinnedMpd(mpd_bins);

		std::string path_2_write = gen.path_2_output+gen.ids[ii]+".dat";
		c.writeMpd(path_2_write);
		std::cout << "map " << ii+1 << "/" << gen.ids.size() << " done" << std::endl;
	}

	std::cout << "Done." << std::endl;
	return 0;
}
