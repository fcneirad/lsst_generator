#!/bin/bash -f
#HERE=${GERLUMPH_PATH_CODES}LSST_simulator/v2.0
HERE='.'
gcc -std=c++11 -o $HERE/gerlumph_part -lstdc++ -lm -lgerlumph -ljsoncpp -lCCfits -lcfitsio -lcudart -lcufft $HERE/gerlumph_part.cpp $HERE/auxiliary_functions.cpp -I/home/fneira/libraries/gerlumphpp/include -L/home/fneira/libraries/gerlumphpp/lib -I/home/fneira/libraries/CCfits/include -L/home/fneira/libraries/CCfits/lib #-I/home/fneira/libraries/cfitsio/include -L/home/fneira/libraries/cfitsio/lib

nvcc -std=c++11 -o $HERE/convolve_map -lgerlumph -ljsoncpp $HERE/convolve_map.cpp $HERE/auxiliary_functions.cpp -L /home/favio/software/gerlumphpp/lib -I /home/favio/software/gerlumphpp/include -L$LIBDIR/jsoncpp/lib -I$LIBDIR/jsoncpp/include

nvcc -std=c++11 -o $HERE/micro_mag_hist -lgerlumph -ljsoncpp $HERE/micro_mag_hist.cpp $HERE/auxiliary_functions.cpp -L /home/favio/software/gerlumphpp/lib -I /home/favio/software/gerlumphpp/include -L$LIBDIR/jsoncpp/lib -I$LIBDIR/jsoncpp/include

nvcc -std=c++11 -o $HERE/micro_mag_hist_pixel -lgerlumph -ljsoncpp $HERE/micro_mag_hist_pixel.cpp $HERE/auxiliary_functions.cpp -L /home/favio/software/gerlumphpp/lib -I /home/favio/software/gerlumphpp/include -L$LIBDIR/jsoncpp/lib -I$LIBDIR/jsoncpp/include
