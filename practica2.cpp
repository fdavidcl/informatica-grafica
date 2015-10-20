// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 2  (implementación)
// **
// *********************************************************************

#include "aux.hpp"
#include "tuplasg.hpp"   // Tupla3f
#include "practica2.hpp"
#include <cmath>

unsigned p2_objeto_activo = 0;


// ---------------------------------------------------------------------
// Función para implementar en la práctica 2 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL.

void P2_Inicializar(int argc, char *argv[]) {
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
