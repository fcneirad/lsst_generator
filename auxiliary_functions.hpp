#ifndef AUXILIARY_HPP
#define AUXILIARY_HPP

#include <vector>
#include <string>
#include "gerlumph.hpp"

class lsstParameters {
public:
  int Nfilters = 6;
  std::vector< std::vector<double> > times;
  std::vector< std::vector<double> > depths;
  std::vector<std::string> filters;
  double tmin;
  double tmax;
  double errbase[6];

  lsstParameters(const std::string filename);
};

class genericParameters {
public:
  std::vector<std::string> ids;
  std::vector<double> mass;
  std::vector<double> gamma_angle;
  std::vector<double> lrest;    // in [nm]
  double Rein;
  int Nlc;
  int seed;
  bool velocities;
  bool start_end;
  std::string path_2_output;

  genericParameters(const std::string filename);
};

class velocityParameters {
public:
  double ra;         // in hours
  double dec;        // in deg
  double sigma_l;    // km/s
  double sigma_s;    // km/s
  double sigma_disp; // km/s
  double epsilon;
  double zl;
  double zs;
  double Dl;
  double Ds;
  double Dls;

  velocityParameters(const std::string filename);
};

double m52snr(double dm);
std::vector<double> calculateRhalf(const std::string filename);
std::vector<gerlumph::FactoryProfile> createProfileParsFromInput(const std::string filename);
std::vector<gerlumph::BaseProfile*> createProfilesFromInput(const std::string filename,double pixSizePhys);
void writeUncompressedData(std::string path,lsstParameters lsst,gerlumph::LightCurveCollection& mother,const std::vector<gerlumph::LightCurveCollection>& full,const std::vector<gerlumph::LightCurveCollection>& sampled);
void writeUncompressedDataNew(std::string path,lsstParameters lsst,gerlumph::LightCurveCollection& mother,const std::vector<gerlumph::LightCurveCollection>& full,const std::vector<gerlumph::LightCurveCollection>& sampled);
void writeCompressedData(std::string path,lsstParameters lsst,gerlumph::LightCurveCollection& mother,const std::vector<gerlumph::LightCurveCollection>& full,const std::vector<gerlumph::LightCurveCollection>& sampled);

#endif /* AUXILIARY_HPP */
