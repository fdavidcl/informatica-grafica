/**********************************************************************
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
**********************************************************************/

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
