#ifndef __MALLA_BAR
#define __MALLA_BAR
#include "MallaInd.hpp"

class MallaBarrido : public MallaInd {
protected:
  std::vector<float> figura;
  Tupla3f vector_traslacion;

public:
  MallaBarrido(const char * filename, unsigned num_traslaciones, Tupla3f vect, std::string nombre = "Malla de barrido");
  void construir(unsigned num_traslaciones);
};

#endif
