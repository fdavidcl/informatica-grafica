#include "NodoGrafoEscena.hpp"
#include "aux.hpp"

void NodoGrafoEscena::visualizar(unsigned modo_vis) {
  // Operamos sobre la modelview
  glMatrixMode(GL_MODELVIEW);
  // Guarda modelview actual
  glPushMatrix();

  glColor3f(color(R), color(G), color(B));

  // Recorrer las entradas del nodo
  for (unsigned i = 0; i < entradas.size(); i++) {
    if (entradas[i].tipoE == 0) {
      // Visualizar los sub-objetos
      entradas[i].objeto->visualizar(modo_vis);
    } else {
      // Componer las transformaciones
      glMultMatrixf(*(entradas[i].matriz));
    }
  }

  glMatrixMode(GL_MODELVIEW);
  // Recuperar la modelview guardada
  glPopMatrix();
}

void NodoGrafoEscena::agregar(EntradaNGE * entrada) {
  entradas.push_back(*entrada);
}

void NodoGrafoEscena::agregar(Objeto3D * pObjeto) {
  entradas.push_back(EntradaNGE(pObjeto));
  pObjeto->setColor(this->color);
}

void NodoGrafoEscena::agregar(const Matriz4f& pMatriz) {
  entradas.push_back(EntradaNGE(pMatriz));
}
