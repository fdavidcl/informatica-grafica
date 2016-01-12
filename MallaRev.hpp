#ifndef __MALLA_REV
#define __MALLA_REV
#include "MallaInd.hpp"

class MallaRevol : public MallaInd {
protected:
  std::vector<float> perfil;
  float altera_x(float, double);
  float altera_z(float, double);

public:
  MallaRevol(const char * filename, unsigned num_perfiles, std::string nombre = "Malla de revolución");
  void construir(unsigned num_perfiles);
};

#endif
