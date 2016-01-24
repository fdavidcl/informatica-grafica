#ifndef __MALLA_PLY
#define __MALLA_PLY
#include "MallaInd.hpp"

class MallaPly : public MallaInd {
public:
  MallaPly(const char * filename, std::string nombre = "Malla PLY");
};

#endif
