#ifndef MALLAIND_HPP
#define MALLAIND_HPP

#include "Objeto3D.hpp"
#include "tuplasg.hpp"
#include <vector>

// Clase derivada de Objeto3D para representación de mallas indexadas
class MallaInd : public Objeto3D
{
   protected:
     std::vector<Tupla3f> vertex_coords;
     std::vector<Tupla3i> indexes;

   public:
     //MallaInd() :color(0,0,0) {}
     virtual void visualizar(unsigned modo_vis);

     void imprimir();
};

#endif
