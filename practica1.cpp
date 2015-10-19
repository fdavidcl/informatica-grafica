// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 1  (implementación)
// **
// *********************************************************************

#include "aux.hpp"
#include "tuplasg.hpp"   // Tupla3f
#include "practica1.hpp"
#include <cmath>

unsigned objeto_activo = 0; // objeto activo: cubo (0), tetraedro (1), otros....

// ---------------------------------------------------------------------
// declaraciones de estructuras de datos....

std::vector<MallaInd> figuras;
unsigned material, precision;

// ---------------------------------------------------------------------
// Función para implementar en la práctica 1 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL.

void P1_Inicializar(int argc, char *argv[]) {
  material = 1;
  precision = 1;
  figuras.push_back(Cubo());
  figuras.push_back(Tetraedro());
  figuras.push_back(Cono(precision));
  figuras.push_back(Cilindro(precision));
}

// ---------------------------------------------------------------------
// Función invocada al pulsar una tecla con la práctica 1 activa:
// (si la tecla no se procesa en el 'main').
//
//  - devuelve 'true' si la tecla se usa en esta práctica para cambiar
//    entre el cubo, el tetraedro u otros objetos (cambia el valor de
//    'objeto_activo').
//  - devuelve 'false' si la tecla no se usa en esta práctica (no ha
//    cambiado nada)

bool P1_FGE_PulsarTeclaNormal(unsigned char tecla) {
  if (tecla >= '0' && tecla <= '9') {
    precision = tecla - '0' + 10 * (tecla == '0');
    figuras[2] = Cono(precision);
    figuras[3] = Cilindro(precision);
  }
  else if (tecla == ' ') {
    ++objeto_activo %= figuras.size();
  }
  else {
    return false;
  }

  return true;
}


// ---------------------------------------------------------------------
// Función a implementar en la práctica 1  para dibujar los objetos
// modo: 0 - puntos, 1 - alambre, 2 - sólido, 3 - sólido ajedrez , >=4 otros....

void P1_DibujarObjetos(unsigned modo) {
  figuras[objeto_activo].visualizar(modo);
}

Cubo::Cubo() {
  vertex_coords.push_back(Tupla3f(0,0,1)); // 0
  vertex_coords.push_back(Tupla3f(1,0,0)); // 1
  vertex_coords.push_back(Tupla3f(1,1,0)); // 2
  vertex_coords.push_back(Tupla3f(0,1,0)); // 3
  vertex_coords.push_back(Tupla3f(0,0,0)); // 4
  vertex_coords.push_back(Tupla3f(1,0,1)); // 5
  vertex_coords.push_back(Tupla3f(1,1,1)); // 6
  vertex_coords.push_back(Tupla3f(0,1,1)); // 7

  // Orden: inferior, izquierda, posterior, superior, derecha y frontal

  indexes.push_back(Tupla3i(0,5,4));
  indexes.push_back(Tupla3i(4,5,1));

  indexes.push_back(Tupla3i(0,4,3));
  indexes.push_back(Tupla3i(3,7,0));

  indexes.push_back(Tupla3i(4,1,2));
  indexes.push_back(Tupla3i(3,4,2));

  indexes.push_back(Tupla3i(2,3,7));
  indexes.push_back(Tupla3i(7,6,2));

  indexes.push_back(Tupla3i(6,5,1));
  indexes.push_back(Tupla3i(1,2,6));

  indexes.push_back(Tupla3i(0,6,7));
  indexes.push_back(Tupla3i(0,5,6));
}

Tetraedro::Tetraedro() {
  // Base: (-sqrt(2)sin(15), 0, -sqrt(2)sin(15)), (1, 0, 0), (0, 0, 1)
  const float offset = -0.366025404;
  vertex_coords.push_back(Tupla3f(offset,0,offset));
  vertex_coords.push_back(Tupla3f(0,0,1));
  vertex_coords.push_back(Tupla3f(1,0,0));

  // Punto superior, offset 1 - 2/3 sqrt(2)sin(60)
  const float off2 = 0.183503419;
  const float height = 0.816496581;
  vertex_coords.push_back(Tupla3f(off2,height,off2));

  indexes.push_back(Tupla3i(0,1,2));
  indexes.push_back(Tupla3i(0,2,3));
  indexes.push_back(Tupla3i(0,1,3));
  indexes.push_back(Tupla3i(1,2,3));
}

Cono::Cono(unsigned prec) {
  const unsigned N = 10 * prec;
  const double PI = 3.1415926;

  const double height = 2;

  // Calculamos vértices en la circunferencia base
  for (unsigned i = 0; i < N; i++) {
    vertex_coords.push_back(Tupla3f(cos(i * 2 * PI / N), 0, sin(i * 2 * PI / N)));
  }
  vertex_coords.push_back(Tupla3f(0,0,0)); // N
  vertex_coords.push_back(Tupla3f(0,height,0)); // N + 1

  // Añadimos triángulos en el círculo base
  for (unsigned i = 0; i < N; i++) {
    indexes.push_back(Tupla3i(N, i, (i + 1)%N));
  }

  // Añadimos triángulos para la cara lateral
  for (unsigned i = 0; i < N; i++) {
    indexes.push_back(Tupla3i(N + 1, i, (i + 1)%N));
  }
}

Cilindro::Cilindro(unsigned prec) {
  const unsigned N = 10 * prec;
  const double PI = 3.1415926;

  const double height = 2;

  // Calculamos vértices en la circunferencia base inferior
  for (unsigned i = 0; i < N; i++) {
    vertex_coords.push_back(Tupla3f(cos(i * 2 * PI / N), 0, sin(i * 2 * PI / N)));
  }
  // Calculamos vértices en la circunferencia base superior
  for (unsigned i = 0; i < N; i++) {
    vertex_coords.push_back(Tupla3f(cos(i * 2 * PI / N), height, sin(i * 2 * PI / N)));
  }
  vertex_coords.push_back(Tupla3f(0,0,0)); // 2N
  vertex_coords.push_back(Tupla3f(0,height,0)); // 2N + 1

  // Añadimos triángulos en el círculo base inferior
  for (unsigned i = 0; i < N; i++) {
    indexes.push_back(Tupla3i(2*N, i, (i + 1)%N));
  }

  // Añadimos triángulos en el círculo base superior
  for (unsigned i = 0; i < N; i++) {
    indexes.push_back(Tupla3i(2*N + 1, N + i, N + (i + 1)%N));
  }

  // Añadimos triángulos para la cara lateral
  for (unsigned i = 0; i < N; i++) {
    // Triángulo con base abajo
    indexes.push_back(Tupla3i(i, (i + 1)%N, N + i));
    // Triángulo con base arriba
    indexes.push_back(Tupla3i(N + i, (i + 1)%N, N + (i + 1)%N));
  }
}
