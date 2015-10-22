#ifndef __MALLA_REV
#define __MALLA_REV
#include "MallaInd.hpp"

class MallaRevol : public MallaInd {
protected:
  std::vector<float> perfil;

public:
  MallaRevol(const char * filename, unsigned num_perfiles);
  void construir(unsigned num_perfiles);
};

#endif
