#include "MallaInd.hpp"
#include "aux.hpp"
#include <algorithm>

/*************************
Método visualizar utilizando
la función glDrawElements.
*************************/
void MallaInd::visualizar(ContextoVis cv) {
  // Comprobación de parámetros
  if (cv.modo_vis > 5 || cv.modo_vis < 0) {
    cv.modo_vis = 2; // Asumimos sólido
  }

  const GLenum modo[] = {GL_POINT, GL_LINE, GL_FILL, GL_FILL, GL_FILL, GL_FILL};

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertex_coords.front());
  glPolygonMode(GL_FRONT_AND_BACK, modo[cv.modo_vis]);

  if (cv.modo_vis < 3) {
    glColor3f(color(R), color(G), color(B));
    glDrawElements(GL_TRIANGLES, 3 * indexes.size(), GL_UNSIGNED_INT, &indexes.front());
  } else if (cv.modo_vis == 3) { // Ajedrez
    for (unsigned i = 0; i < indexes.size(); i++) {
      float tone = 0.8 * (i % 2); // 0.8 if i is odd
      glColor3f(tone, tone, tone);
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &indexes[i]);
    }
  } else if (cv.modo_vis == 4) {
    glShadeModel(GL_FLAT);

    if (!text_coords.empty()) {
      glTexCoordPointer(2, GL_FLOAT, 0, &text_coords.front());
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    if (!normales_vertices.empty()) {
      glNormalPointer(GL_FLOAT, 0, &normales_vertices.front());
      glEnableClientState(GL_NORMAL_ARRAY);
    }

    glDrawElements(GL_TRIANGLES, 3 * indexes.size(), GL_UNSIGNED_INT, &indexes.front());

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

  } else if (cv.modo_vis == 5) {
    glShadeModel(GL_SMOOTH);

    if (!text_coords.empty()) {
      glTexCoordPointer(2, GL_FLOAT, 0, &text_coords.front());
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    if (!normales_vertices.empty()) {
      glNormalPointer(GL_FLOAT, 0, &normales_vertices.front());
      glEnableClientState(GL_NORMAL_ARRAY);
    }

    glDrawElements(GL_TRIANGLES, 3 * indexes.size(), GL_UNSIGNED_INT, &indexes.front());

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}

static Tupla3f normalizar(Tupla3f t) {
  return (t(X) != 0 || t(Y) != 0 || t(Z) != 0) ? t.normalized() : Tupla3f(1, 0, 0);
}

void MallaInd::calcularNormales() {
  normales_vertices.resize(vertex_coords.size());
  std::fill(normales_vertices.begin(), normales_vertices.end(), Tupla3f(0, 0, 0));

  for (std::vector<Tupla3i>::iterator cara = indexes.begin(); cara != indexes.end(); ++cara) {
    Tupla3f
      p = vertex_coords[(*cara)(0)],
      q = vertex_coords[(*cara)(1)],
      r = vertex_coords[(*cara)(2)],

      // Vectores correspondientes a dos aristas
      a = q - p,
      b = r - p,

      // Vector ortogonal a la cara
      ortogonal = a.cross(b);

    normales_caras.push_back(ortogonal);

    // Sumamos ahora el normal a la cara a los vectores que
    // corresponden a los vértices
    for (int v = 0; v < 3; ++v)
      normales_vertices[(*cara)(v)] = normales_vertices[(*cara)(v)] + ortogonal;
  }

  // Normalizamos todos los vectores (para máxima eficiencia usamos transform)
  std::transform(normales_caras.begin(), normales_caras.end(),
                 normales_caras.begin(), normalizar);

  std::transform(normales_vertices.begin(), normales_vertices.end(),
                 normales_vertices.begin(), normalizar);
}

/*************************
Método visualizar utilizando
las funciones glBegin y glEnd.
************************** /
void MallaInd::visualizar(ContextoVis cv) {
  // Comprobación de parámetros
  if (cv.modo_vis > 3 || cv.modo_vis < 0) {
    cv.modo_vis = 2;
  }

  const GLenum modo[] = {GL_POINTS, GL_LINES, GL_TRIANGLES, GL_TRIANGLES};

  glBegin(modo[cv.modo_vis]);
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
