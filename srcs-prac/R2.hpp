/**********************************************************************
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
**********************************************************************/

#ifndef __R2
#define __R2
#include "NodoGrafoEscena.hpp"

class ProjR2 : public NodoGrafoEscena {
public:
  ProjR2(float offset);

  void extender(float offset);
};

class Camara : public NodoGrafoEscena {
public:
  Camara();
};

class CabezaR2 : public NodoGrafoEscena {
private:
  ProjR2 * pr;
public:
  CabezaR2(float giro, float offset);
  void girar(float giro);
  void extender(float offset) {
    pr->extender(offset);
  }
};

class CuerpoR2 : public NodoGrafoEscena {
public:
  CuerpoR2();
};

class BrazoSuperior : public NodoGrafoEscena {
public:
  BrazoSuperior();
};

class LadoBrazo : public NodoGrafoEscena {
public:
  LadoBrazo();
};

class BrazoR2 : public NodoGrafoEscena {
public:
  BrazoR2(float giro, float offset);
  void girar(float giro);
  void extender(float offset);
};

class PataR2 : public NodoGrafoEscena {
public:
  PataR2();
};

class R2 : public NodoGrafoEscena {
private:
  CabezaR2 * cabeza;
  BrazoR2 * izquierdo, * derecho;

public:
  static const float DEFAULT_VALUE;
  R2();
  void girar_cabeza(float giro) {
    cabeza->girar(giro);
  }
  void girar_brazos(float giro) {
    izquierdo->girar(giro);
    derecho->girar(giro);
  }
  void extender_proj(float offset) {
    cabeza->extender(offset);
  }
  void extender_brazos(float offset) {
    izquierdo->extender(offset);
    derecho->extender(offset);
  }
};

#endif
