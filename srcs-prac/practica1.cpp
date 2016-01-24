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

// Configuración del torp
const double
  DEFAULT_MAJOR_RADIUS = 1,
  DEFAULT_MINOR_RADIUS = 0.5;

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
  figuras.push_back(Toro(DEFAULT_MAJOR_RADIUS, DEFAULT_MINOR_RADIUS, precision));
  figuras.push_back(Moebius(precision));
  figuras.push_back(Klein(precision));
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
  tecla = tolower(tecla);

  if (tecla >= '0' && tecla <= '9') {
    precision = tecla - '0' + 10 * (tecla == '0');
    figuras[2] = Cono(precision);
    figuras[3] = Cilindro(precision);
    figuras[4] = Toro(DEFAULT_MAJOR_RADIUS, DEFAULT_MINOR_RADIUS, precision);
    figuras[5] = Moebius(precision);
    figuras[6] = Klein(precision);
  }
  else if (tecla == ' ' || tecla == '.' || tecla == 'o') {
    ++objeto_activo %= figuras.size();
    std::cerr << "Objeto actual: " << figuras[objeto_activo].nombre() << std::endl;
  }
  else if (tecla == ',') {
    objeto_activo = (objeto_activo + figuras.size() - 1)% figuras.size();
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

Cubo::Cubo(std::string nombre) {
  nombre_obj = nombre;

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

Tetraedro::Tetraedro(std::string nombre) {
  nombre_obj = nombre;

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

Cono::Cono(unsigned prec, std::string nombre) {
  nombre_obj = nombre;

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

Cilindro::Cilindro(unsigned prec, std::string nombre) {
  nombre_obj = nombre;

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

Tupla3f Toro::vertice(double theta, double phi) {
  return Tupla3f(
    (rad_ext + rad_int * cos(theta)) * cos(phi),
    (rad_ext + rad_int * cos(theta)) * sin(phi),
    rad_int * sin(theta)
  );
}

Toro::Toro(double R, double r, unsigned prec, std::string nombre)
  :rad_ext(R), rad_int(r) {
  nombre_obj = nombre;

  const unsigned N = 10 * prec;
  const double TAU = 6.2831853; // τ = 2π

  // Añadimos vértices con la precisión dada
  for (unsigned i = 0; i < N; ++i) {
    double theta = (double)(i) / N * TAU;

    // Vértices i*N a i*N + (N - 1)
    for (unsigned j = 0; j < N; ++j) {
      // Vértice i*N + j
      double phi = (double)(j) / N * TAU;

      vertex_coords.push_back(vertice(theta, phi));
    }
  }

  // Añadimos caras
  // Recorriendo círculo exterior
  for (unsigned i = 0; i < N; ++i) {
    // Recorriendo círculo interior
    for (unsigned j = 0; j < N; ++j) {
      // Unir cada punto del círculo con el que está en la misma posición en
      // el siguiente círculo y con los adyacentes
      indexes.push_back(Tupla3i(i*N + j, ((i + 1)%N)*N + j, i*N + (j + 1)%N));
      indexes.push_back(Tupla3i(((i + 1)%N)*N + j, ((i + 1)%N)*N + (j + 1)%N, i * N + (j + 1)%N));
    }
  }

}

Tupla3f Moebius::vertice(double u, double v) {
  return Tupla3f(
    (1 + (v - 1)/2 * cos(u/2)) * cos(u),
    (1 + (v - 1)/2 * cos(u/2)) * sin(u),
    (v - 1)/2 * sin(u/2)
  );
}

Moebius::Moebius(unsigned prec, std::string nombre) {
  nombre_obj = nombre;

  const unsigned N = 10 * prec;
  const double TAU = 6.2831853; // τ = 2π

  const double LIMIT_U = TAU;
  const double LIMIT_V = 2;

  // Añadimos vértices con la precisión dada
  for (unsigned i = 0; i < N; ++i) {
    double u = (double)(i) / N * LIMIT_U;

    // Vértices i*N a i*N + (N - 1)
    for (unsigned j = 0; j < N; ++j) {
      // Vértice i*N + j
      double v = (double)(j) / N * LIMIT_V;

      vertex_coords.push_back(vertice(u, v));
    }
  }

  // Añadimos caras
  for (unsigned i = 0; i < N - 1; ++i) {
    for (unsigned j = 0; j < N - 1; ++j) {
      // Unir cada punto del círculo con el que está en la misma posición en
      // el siguiente círculo y con los adyacentes
      indexes.push_back(Tupla3i(i*N + j, ((i + 1)%N)*N + j, i*N + (j + 1)%N));
      indexes.push_back(Tupla3i(((i + 1)%N)*N + j, ((i + 1)%N)*N + (j + 1)%N, i * N + (j + 1)%N));
    }
  }

  // La última fila de vértices hay que unirla con los opuestos de la primera!
  for (unsigned j = 0; j < N - 1; ++j) {
    indexes.push_back(Tupla3i((N - 1)*N + j, (N - j - 1)%N, (N - 1)*N + (j + 1)%N));
    indexes.push_back(Tupla3i((N - j - 2)%N, (N - j - 1)%N, (N - 1) * N + (j + 1)%N));
  }

}

Tupla3f Klein::vertice(double u, double v) {
  double cosu = cos(u), cosv = cos(v),
    sinu = sin(u), sinv = sin(v);

  // Ecuaciones paramétricas de la proyección tridimensional
  // de la botella de Klein obtenidas de Wikipedia:
  // https://en.wikipedia.org/wiki/Klein_bottle#Bottle_shape
  return Tupla3f(
    // x
    -(2.0/15) * cosu * (3 * cosv - 30 * sinu + 90 * pow(cosu, 4) * sinu
    - 60 * pow(cosu, 6) * sinu + 5 * cosu * cosv * sinu)

    ,// y
    -(1.0/15) * sinu * (3 * cosv - 3 * cosu * cosu * cosv - 48 * pow(cosu, 4) * cosv
    + 48 * pow(cosu, 6) * cosv - 60 * sinu + 5 * cosu * cosv * sinu
    - 5 * pow(cosu, 3) * cosv * sinu - 80 * pow(cosu, 5) * cosv * sinu
    + 80 * pow(cosu, 7) * cosv * sinu)

    ,// z
    (2.0/15) * (3 + 5 * cosu * sinu) * sinv
  );
}

Klein::Klein(unsigned prec, std::string nombre) {
  nombre_obj = nombre;

  const unsigned N = 10 * prec;
  const double TAU = 6.2831853; // τ = 2π

  const double LIMIT_U = TAU/2;
  const double LIMIT_V = TAU;

  // Añadimos vértices con la precisión dada
  for (unsigned i = 0; i < N; ++i) {
    double u = (double)(i) / N * LIMIT_U;

    // Vértices i*N a i*N + (N - 1)
    for (unsigned j = 0; j < N; ++j) {
      // Vértice i*N + j
      double v = (double)(j) / N * LIMIT_V;

      vertex_coords.push_back(vertice(u, v));
    }
  }

  // Añadimos caras
  for (unsigned i = 0; i < N - 1; ++i) {
    for (unsigned j = 0; j < N; ++j) {
      // Unir cada punto del círculo con el que está en la misma posición en
      // el siguiente círculo y con los adyacentes
      indexes.push_back(Tupla3i(i*N + j, ((i + 1)%N)*N + j, i*N + (j + 1)%N));
      indexes.push_back(Tupla3i(((i + 1)%N)*N + j, ((i + 1)%N)*N + (j + 1)%N, i * N + (j + 1)%N));
    }
  }

  // La última fila de vértices hay que unirla con los opuestos de la primera
  for (unsigned j = 0; j < N; ++j) {
    indexes.push_back(Tupla3i((N - 1)*N + j, (N - (j + N/2)%N)%N, (N - 1)*N + (j + 1)%N));
    indexes.push_back(Tupla3i((N - (j + N/2)%N - 1)%N, (N - (j + N/2)%N)%N, (N - 1) * N + (j + 1)%N));
  }

}
