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

unsigned p2_objeto_activo = 0;

MallaInd * p2_figuras[2];


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
    std::stringstream conversor(argv[2]);
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

  return false;
}


// ---------------------------------------------------------------------
// Función a implementar en la práctica 2 para dibujar los objetos
// modo: 0 - puntos, 1 - alambre, 2 - sólido, 3 - sólido ajedrez , >=4 otros....

void P2_DibujarObjetos(unsigned modo) {

}
