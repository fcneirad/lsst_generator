#!/bin/bash -f
#HERE=${GERLUMPH_PATH_CODES}LSST_simulator/v2.0
LIBDIR='/home/favio/software/libraries'
HERE='.'
gcc -std=c++11 -I$LIBDIR/gerlumphpp/include -I$LIBDIR/jsoncpp/include -I$LIBDIR/libpng/include -I$LIBDIR/CCfits/include -I$LIBDIR/cfitsio/include -o $HERE/gerlumph_part $HERE/gerlumph_part.cpp $HERE/auxiliary_functions.cpp -L$LIBDIR/jsoncpp/lib -Wl,-rpath,$LIBDIR/jsoncpp/lib -L$LIBDIR/gerlumphpp/lib -Wl,-rpath,$LIBDIR/gerlumphpp/lib -L$LIBDIR/libpng/lib -Wl,-rpath,$LIBDIR/libpng/lib -L$LIBDIR/CCfits/lib -Wl,-rpath,$LIBDIR/CCfits/lib -L$LIBDIR/cfitsio/lib -Wl,-rpath,$LIBDIR/cfitsio/lib -lgerlumph -ljsoncpp -lpng -lCCfits -lcfitsio -lm -lstdc++
