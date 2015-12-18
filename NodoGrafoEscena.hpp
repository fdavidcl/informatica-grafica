#ifndef __NODOGRAFOESCENA
#define __NODOGRAFOESCENA
#include <vector>
#include "Objeto3D.hpp"
#include "matrizg.hpp"

// typedef unsigned ContextoVis;

struct EntradaNGE {
  // tipoE define el tipo de entrada: 0 = objeto, 1 = transformación
  unsigned char tipoE;
  union {
    Objeto3D * objeto;
    Matriz4f * matriz;
  };

  EntradaNGE(Objeto3D * pObjeto)
    :tipoE(0), objeto(pObjeto) {}
  EntradaNGE(const Matriz4f& pMatriz)
    :tipoE(1), matriz(new Matriz4f(pMatriz)) {}
};

class NodoGrafoEscena : public Objeto3D {
protected:
  std::vector<EntradaNGE> entradas;

public:
  //NodoGrafoEscena() :color(0,0,0) {}
  // Método para visualizar usando OpenGL
  virtual void visualizar(unsigned modo_vis);

  // Métodos para añadir una entrada al final
  void agregar(EntradaNGE * entrada);
  void agregar(Objeto3D * pObjeto);
  void agregar(const Matriz4f& pMatriz);
};

#endif
