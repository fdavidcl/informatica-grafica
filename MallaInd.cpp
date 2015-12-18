#include "MallaInd.hpp"
#include "aux.hpp"

/*************************
Método visualizar utilizando
la función glDrawElements.
*************************/
void MallaInd::visualizar(unsigned modo_vis) {
  // Comprobación de parámetros
  if (modo_vis > 3 || modo_vis < 0) {
    std::cerr << "Parámetro modo_vis incorrecto" << std::endl;
    return;
  }

  const GLenum modo[] = {GL_POINT, GL_LINE, GL_FILL, GL_FILL};

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertex_coords.front());
  glPolygonMode(GL_FRONT_AND_BACK, modo[modo_vis]);

  if (modo_vis < 3) {
    glColor3f(color(R), color(G), color(B));
    glDrawElements(GL_TRIANGLES, 3 * indexes.size(), GL_UNSIGNED_INT, &indexes.front());
  } else { // Ajedrez
    for (unsigned i = 0; i < indexes.size(); i++) {
      float tone = 0.8 * (i % 2); // 0.8 if i is odd
      glColor3f(tone, tone, tone);
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &indexes[i]);
    }
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}

/*************************
Método visualizar utilizando
las funciones glBegin y glEnd.
************************** /
void MallaInd::visualizar(unsigned modo_vis) {
  // Comprobación de parámetros
  if (modo_vis > 3 || modo_vis < 0) {
    std::cerr << "Parámetro modo_vis incorrecto" << std::endl;
    return;
  }

  const GLenum modo[] = {GL_POINTS, GL_LINES, GL_TRIANGLES, GL_TRIANGLES};

  glBegin(modo[modo_vis]);
    for (unsigned i = 0; i < indexes.size(); i++) {
      for (unsigned j = 0; j < 3; j++) {
        float tone = 0.8 * (i % 2); // 0.8 if i is odd
        glColor3f(tone, tone, tone);
        glVertex3f(vertex_coords[indexes[i][j]][0], vertex_coords[indexes[i][j]][1], vertex_coords[indexes[i][j]][2]);
      }
    }
  glEnd();
}

/* Método de impresión para depuración */
void MallaInd::imprimir() {
  std::cerr << "Tamaño " << indexes.size() << std::endl;

  for (unsigned i = 0; i < indexes.size(); i++) {
    Tupla3i cur = indexes[i];

    std::cerr << cur << ": ";

    for (unsigned j = 0; j < 3; j++) {
      std::cerr << vertex_coords[cur[j]] << " ";
    }

    std::cerr << std::endl;
  }
  std::cerr << "Hasta aquí" << std::endl;
}
