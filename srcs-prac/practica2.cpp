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
#include "MallaBarrido.hpp"
#include <cmath>
#include <string>
#include <sstream>

static unsigned p2_objeto_activo = 0;
static const unsigned NUM_OBJETOS = 3;
static MallaInd * p2_figuras[NUM_OBJETOS] = {NULL};


// ---------------------------------------------------------------------
// Función para implementar en la práctica 2 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL.

void P2_Inicializar(int argc, char *argv[]) {
  std::string ply_file, rev_file, bar_file;
  unsigned perfiles = 10;
  Tupla3f vec_dir(1, 1, 1);

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
  if (argc < 4) {
    bar_file = "../plys/peon.ply";
  } else {
    bar_file = argv[3];
  }
  if (argc >= 5) {
    std::stringstream conversor(argv[4]);
    conversor >> perfiles;
  }
  if (argc >= 8) {
    for (int i = 0; i < 3; i++) {
      std::stringstream conversor(argv[5 + i]);
      conversor >> vec_dir[i];
    }

    std::cout << vec_dir;
  }


  p2_figuras[0] = new MallaPly(ply_file.c_str());
  p2_figuras[1] = new MallaRevol(rev_file.c_str(), perfiles);
  p2_figuras[2] = new MallaBarrido(bar_file.c_str(), perfiles, vec_dir);
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
    unsigned num = (tecla - '0' + 10 * (tecla == '0'));
    static_cast<MallaRevol*>(p2_figuras[1])->construir(num * 10);
    static_cast<MallaBarrido*>(p2_figuras[2])->construir(num);
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
