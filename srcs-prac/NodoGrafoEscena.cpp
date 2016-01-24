#include "NodoGrafoEscena.hpp"
#include "aux.hpp"

void NodoGrafoEscena::visualizar(ContextoVis cv) {
  // Operamos sobre la modelview
  glMatrixMode(GL_MODELVIEW);
  // Guarda modelview actual
  glPushMatrix();

  glColor3f(color(R), color(G), color(B));

  // Guarda material inicial
  Material * materialActivoInicial = cv.materialActivo;

  // Recorrer las entradas del nodo
  for (unsigned i = 0; i < entradas.size(); i++) {
    if (entradas[i].tipoE == 0) {
      // Visualizar los sub-objetos
      entradas[i].objeto->visualizar(cv);
    } else if (entradas[i].tipoE == 1) {
      // Componer las transformaciones
      glMultMatrixf(*(entradas[i].matriz));
    } else if (entradas[i].tipoE == 2) {
      if (entradas[i].material != cv.materialActivo) {
        cv.materialActivo = entradas[i].material;
        cv.materialActivo->activar();
      }
    }
  }

  // Recupera material inicial
  if (materialActivoInicial != cv.materialActivo) {
    cv.materialActivo = materialActivoInicial;

    if (cv.materialActivo != NULL)
      cv.materialActivo->activar();
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

void NodoGrafoEscena::agregar(Material * p_material) {
  entradas.push_back(EntradaNGE(p_material));
}
