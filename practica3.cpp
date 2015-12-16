// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 2  (implementación)
// **
// *********************************************************************

#include "aux.hpp"
#include "tuplasg.hpp"   // Tupla3f
#include "practica3.hpp"
#include "NodoGrafoEscena.hpp"
#include "R2.hpp"

static unsigned p3_objeto_activo = 0;
static const unsigned NUM_OBJETOS = 3;
static NodoGrafoEscena * p3_figura;


void P3_Inicializar(int argc, char *argv[]) {
  p3_figura = new R2();
}


bool P3_FGE_PulsarTeclaNormal(unsigned char tecla) {
  tecla = tolower(tecla);

  if (tecla >= '0' && tecla <= '9') {
    unsigned num = (tecla - '0' + 10 * (tecla == '0'));
    //static_cast<MallaRevol*>(p2_figuras[1])->construir(num * 10);
    //static_cast<MallaBarrido*>(p2_figuras[2])->construir(num);
  } else {
    return false;
  }

  return true;
}


void P3_DibujarObjetos(unsigned modo) {
  p3_figura->visualizar(modo);
}
