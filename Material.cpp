#include "Material.hpp"

//--------------------------------------------------
// Activación de materiales
void MaterialEstandar::activar() {
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glDisable(GL_COLOR_MATERIAL);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color[0]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color[1]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color[2]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color[3]);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, exponente);

  glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
  glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
  glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  if (text != NULL) {
    //std::cerr << "Habemus textura!" << std::endl << std::flush;
    text->activar();
  }
}

//--------------------------------------------------
// Gestión de texturas
void Textura::activar() {
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, id_text);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  if (mgct == 0) {
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
  } else {
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    if (mgct == 1) {
      glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
      glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

      glTexGenfv(GL_S, GL_OBJECT_PLANE, cs);
      glTexGenfv(GL_T, GL_OBJECT_PLANE, ct);
    } else {
      glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
      glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

      glTexGenfv(GL_S, GL_EYE_PLANE, cs);
      glTexGenfv(GL_T, GL_EYE_PLANE, ct);
    }
  }
}

Textura::Textura(const std::string& archivoJPG, unsigned mgct) :mgct(mgct) {
  img = new jpg::Imagen(archivoJPG);

  cs[0] = ct[2] = 1;
  cs[1] = cs[2] = cs[3] = ct[0] = ct[1] = ct[3] = 0;

  glGenTextures(1, &id_text);
  glBindTexture(GL_TEXTURE_2D, id_text);

  /*
  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGB,
    img->tamX(), img->tamY(),
    0, GL_RGB, GL_UNSIGNED_BYTE,
    img->leerPixels()
  );*/

  gluBuild2DMipmaps(
    GL_TEXTURE_2D,
    GL_RGB,
    img->tamX(), img->tamY(),
    GL_RGB, GL_UNSIGNED_BYTE,
    img->leerPixels()
  );

  glBindTexture(GL_TEXTURE_2D, 0);
}

//--------------------------------------------------
// Materiales concretos

MaterialLata::MaterialLata() {
  text = new Textura("../imgs/lata-coke.jpg", 0);

  Tupla4f blanco(1, 1, 1, 1);
  color[0] = blanco * 0.8;
  color[1] = blanco * 0.1;
  color[2] = blanco * 0.3;
  color[3] = blanco * 0.7;
  exponente = 5;
}

MaterialTapasLata::MaterialTapasLata() {
  text = NULL;

  Tupla4f blanco(1, 1, 1, 1);
  color[0] = blanco * 0.6;
  color[1] = blanco * 0.05;
  color[2] = blanco * 0.2;
  color[3] = blanco * 0.7;
  exponente = 5;
}

MaterialPeonMadera::MaterialPeonMadera() {
  text = new Textura("../imgs/text-madera.jpg", 1);

  Tupla4f blanco(1, 1, 1, 1);
  color[0] = blanco * 0.8;
  color[1] = blanco * 0.1;
  color[2] = blanco * 0.3;
  color[3] = blanco * 0.7;
  exponente = 5;
}

MaterialPeonBlanco::MaterialPeonBlanco() {
  text = NULL;

  Tupla4f blanco(1, 1, 1, 1);
  color[0] = blanco * 0.8;
  color[1] = blanco * 0.05;
  color[2] = blanco * 0.2;
  color[3] = blanco * 0.0;
  exponente = 5;
}

MaterialPeonNegro::MaterialPeonNegro() {
  text = NULL;

  Tupla4f blanco(1, 1, 1, 1);
  color[0] = blanco * 0.001;
  color[1] = blanco * 0.0;
  color[2] = blanco * 0.01;
  color[3] = blanco * 0.7;
  exponente = 5;
}
