#ifndef __MALLA_REV
#define __MALLA_REV
#include "MallaInd.hpp"

class MallaRevol : public MallaInd {
protected:
  std::vector<float> perfil;

  void generar_coords_textura();

public:
  MallaRevol(
    const char * filename,
    unsigned num_perfiles,
    bool usar_textura = false,
    bool base_inferior = true,
    bool base_superior = true,
    std::string nombre = "Malla de revolución"
  );
  void construir(unsigned num_perfiles, bool base_inferior = true, bool base_superior = true);
};

#endif
