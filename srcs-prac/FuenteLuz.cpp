#include "FuenteLuz.hpp"

void ColeccionFL::activar() {
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glDisable(GL_COLOR_MATERIAL);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  for (unsigned f = 0; f < fuentes.size(); ++f) {
    fuentes.at(f)->activar();
  }
}

void FuenteLuz::activar() {
  glEnable(GL_LIGHT0 + index);

  glLightfv(GL_LIGHT0 + index, GL_AMBIENT, colores[0]);
  glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, colores[1]);
  glLightfv(GL_LIGHT0 + index, GL_SPECULAR, colores[2]);

  if (posvec[3] == 1) { // => posicional
    glLightfv(GL_LIGHT0 + index, GL_POSITION, posvec);
  } else {
    // Entramos en la modelview
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glRotatef(longi, 0.0, 1.0, 0.0);
    glRotatef(lati, -1.0, 0.0, 0.0);
    glLightfv(GL_LIGHT0 + index, GL_POSITION, Tupla4f(0, 0, 1, 0));

    glPopMatrix();
  }
}

FuentePosicional::FuentePosicional(int index, const Tupla3f& posicion)
  :FuenteLuz(index, 0, 0, Tupla4f(posicion(X), posicion(Y), posicion(Z), 1)) {
  for (int i = 0; i < 3; i++)
    // Luz azulada
    colores[i] = Tupla4f(0.5, 0.7, 0.8, 1);
}

FuenteDireccional::FuenteDireccional(int index, float longi, float lati)
  :FuenteLuz(index, longi, lati, Tupla4f(0, 0, 0, 0)) {
  for (int i = 0; i < 3; i++)
    // Luz blanca
    colores[i] = Tupla4f(0.7, 0.7, 0.7, 1);
}

void FuenteDireccional::variarAngulo(unsigned angulo, float incremento) {
  if (angulo)
    longi += incremento;
  else
    lati += incremento;

  activar();
}

ColeccionFuentesP4::ColeccionFuentesP4() {
  fuentes.push_back(
    new FuenteDireccional(0, 0, 0)
  );
  fuentes.push_back(
    new FuentePosicional(1, Tupla3f(5, 5, 0))
  );
}
