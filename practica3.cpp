// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 2  (implementación)
// **
// *********************************************************************

#include "aux.hpp"
#include "tuplasg.hpp"   // Tupla3f
#include "practica3.hpp"
//#include "MallaInd.hpp"

static unsigned p3_objeto_activo = 0;
static const unsigned NUM_OBJETOS = 3;
static MallaInd * p3_figuras[NUM_OBJETOS] = {NULL};


void P3_Inicializar(int argc, char *argv[]) {

}


bool P3_FGE_PulsarTeclaNormal(unsigned char tecla) {
  tecla = tolower(tecla);

  if (tecla >= '0' && tecla <= '9') {
    unsigned num = (tecla - '0' + 10 * (tecla == '0'));
    //static_cast<MallaRevol*>(p2_figuras[1])->construir(num * 10);
    //static_cast<MallaBarrido*>(p2_figuras[2])->construir(num);
  } else if (tecla == ' ' || tecla == '.' || tecla == 'o') {
    ++p3_objeto_activo %= NUM_OBJETOS;
    std::cerr << "Objeto actual: " << p2_figuras[p2_objeto_activo]->nombre() << std::endl;
  } else if (tecla == ',') {
    p3_objeto_activo = (p3_objeto_activo + NUM_OBJETOS - 1) % NUM_OBJETOS;
  } else {
    return false;
  }

  return true;
}


void P3_DibujarObjetos(unsigned modo) {
  p3_figuras[p3_objeto_activo]->visualizar(modo);
}
