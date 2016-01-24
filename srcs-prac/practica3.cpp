// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 3  (implementación)
// **
// *********************************************************************

#include "aux.hpp"
#include "tuplasg.hpp"   // Tupla3f
#include "practica3.hpp"
#include "NodoGrafoEscena.hpp"
#include "R2.hpp"

typedef void (R2::*R2Method)(float);

static unsigned p3_objeto_activo = 0;
static const unsigned NUM_OBJETOS = 3;
static R2 * p3_figura;

static const unsigned GRADOS_LIBERTAD = 4;
static unsigned p3_grado_libertad_activo = 0;
static float p3_valores[GRADOS_LIBERTAD] = {R2::DEFAULT_VALUE,R2::DEFAULT_VALUE,R2::DEFAULT_VALUE,R2::DEFAULT_VALUE};
static R2Method funciones_cambios[GRADOS_LIBERTAD] = {
  &R2::girar_cabeza,
  &R2::extender_proj,
  &R2::girar_brazos,
  &R2::extender_brazos
};
static const std::string p3_grados_nombres[GRADOS_LIBERTAD] = {
  "Giro cabeza",
  "Desplazamiento proyector cabeza",
  "Giro brazos",
  "Desplazamiento brazos"
};

void P3_Inicializar(int argc, char *argv[]) {
  p3_figura = new R2();
}


bool P3_FGE_PulsarTeclaNormal(unsigned char tecla) {
  // Si pulsamos mayúsculas usamos signo negativo
  int signo = 1 - 2 * (tecla != tolower(tecla));
  tecla = tolower(tecla);

  if (tecla == 'g') {
    p3_grado_libertad_activo = (p3_grado_libertad_activo + 1) % GRADOS_LIBERTAD;
    std::cout << "Cambiado grado de libertad a '" << p3_grados_nombres[p3_grado_libertad_activo] << "' con valor " << p3_valores[p3_grado_libertad_activo] << std::endl;
  } else if (tecla == '<' || tecla == '>' || tecla == 'z' || tecla == 'x' || tecla == 'c' || tecla == 'v') {
    unsigned grado = p3_grado_libertad_activo;

    if (tecla == '<' || tecla == '>')
      signo = 1 - 2 * (tecla == '<');
    else
      grado = (tecla == 'x') + 2 * (tecla == 'c') + 3 * (tecla == 'v');

    float nuevo = p3_valores[grado] + signo/100.0;

    if (nuevo >= 0 && nuevo <= 1) {
      (p3_figura->*funciones_cambios[grado])(nuevo);
      std::cout << "Ajustado grado de libertad '" << p3_grados_nombres[grado] << "' con valor " << nuevo << std::endl;
      p3_valores[grado] += signo/100.0;
    }

  } else {
    return false;
  }

  return true;
}


void P3_DibujarObjetos(unsigned modo) {
  p3_figura->visualizar(modo);
}
