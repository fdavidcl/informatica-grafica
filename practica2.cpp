// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 2  (implementación)
// **
// *********************************************************************

#include "aux.hpp"
#include "tuplasg.hpp"   // Tupla3f
#include "practica2.hpp"
#include "MallaInd.hpp"
#include "MallaPly.hpp"
#include "MallaRev.hpp"
#include <cmath>
#include <string>
#include <sstream>

static unsigned p2_objeto_activo = 0;
static const unsigned NUM_OBJETOS = 2;
static MallaInd * p2_figuras[NUM_OBJETOS];


// ---------------------------------------------------------------------
// Función para implementar en la práctica 2 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL.

void P2_Inicializar(int argc, char *argv[]) {
  std::string ply_file, rev_file;
  unsigned perfiles = 10;

  if (argc < 2) {
    ply_file = "../plys/beethoven.ply";
  } else {
    ply_file = argv[1];
  }
  if (argc < 3) {
    rev_file = "../plys/peon.ply";
  } else {
    rev_file = argv[2];
  }
  if (argc >= 4) {
    std::stringstream conversor(argv[3]);
    conversor >> perfiles;
  }

  p2_figuras[0] = new MallaPly(ply_file.c_str());
  p2_figuras[1] = new MallaRevol(rev_file.c_str(), perfiles);
}

// ---------------------------------------------------------------------
// Función invocada al pulsar una tecla con la práctica 2 activa:
// (si la tecla no se procesa en el 'main').
//
//  - devuelve 'true' si la tecla se usa en esta práctica para cambiar
//    entre el cubo, el tetraedro u otros objetos (cambia el valor de
//    'objeto_activo').
//  - devuelve 'false' si la tecla no se usa en esta práctica (no ha
//    cambiado nada)

bool P2_FGE_PulsarTeclaNormal(unsigned char tecla) {
  tecla = tolower(tecla);

  if (tecla >= '0' && tecla <= '9') {
    unsigned num_perf = (tecla - '0' + 10 * (tecla == '0')) * 10;
    static_cast<MallaRevol*>(p2_figuras[1])->construir(num_perf);
  } else if (tecla == ' ' || tecla == '.' || tecla == 'o') {
    ++p2_objeto_activo %= NUM_OBJETOS;
    std::cerr << "Objeto actual: " << p2_figuras[p2_objeto_activo]->nombre() << std::endl;
  } else if (tecla == ',') {
    p2_objeto_activo = (p2_objeto_activo + NUM_OBJETOS - 1) % NUM_OBJETOS;
  } else {
    return false;
  }

  return true;
}


// ---------------------------------------------------------------------
// Función a implementar en la práctica 2 para dibujar los objetos
// modo: 0 - puntos, 1 - alambre, 2 - sólido, 3 - sólido ajedrez , >=4 otros....

void P2_DibujarObjetos(unsigned modo) {
  p2_figuras[p2_objeto_activo]->visualizar(modo);
}
