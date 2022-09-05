#!/bin/bash -f
#HERE=${GERLUMPH_PATH_CODES}LSST_simulator/v2.0
HERE='.'
gcc -std=c++11 -I/home/favio/software/libraries/gerlumphpp/include -o $HERE/gerlumph_part $HERE/gerlumph_part.cpp $HERE/auxiliary_functions.cpp -L/home/favio/software/libraries/gerlumphpp/lib -Wl,-rpath,/home/favio/software/libraries/gerlumphpp/lib -lgerlumph -ljsoncpp -lm -lstdc++
#gcc -std=c++11 -lgerlumph -ljsoncpp -o $HERE/gerlumph_part $HERE/gerlumph_part.cpp $HERE/auxiliary_functions.cpp
#nvcc -std=c++11 -o $HERE/convolve_map -lgerlumph -ljsoncpp $HERE/convolve_map.cpp $HERE/auxiliary_functions.cpp -L /home/favio/software/gerlumphpp/lib -I /home/favio/software/gerlumphpp/include
