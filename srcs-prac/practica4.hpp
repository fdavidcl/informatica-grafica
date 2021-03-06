/**********************************************************************
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
**********************************************************************/

#ifndef IG_PRACTICA4_HPP
#define IG_PRACTICA4_HPP
#include "NodoGrafoEscena.hpp"

void P4_Inicializar(int argc, char *argv[]);
bool P4_FGE_PulsarTeclaNormal(unsigned char tecla);
void P4_DibujarObjetos(ContextoVis modo);

class Escena : public NodoGrafoEscena {
public:
  Escena();
};

class Lata : public NodoGrafoEscena {
public:
  Lata();
};

class LateralLata : public NodoGrafoEscena {
public:
  LateralLata();
};

class BaseInfLata : public NodoGrafoEscena {
public:
  BaseInfLata();
};

class BaseSupLata : public NodoGrafoEscena {
public:
  BaseSupLata();
};

class Peon : public NodoGrafoEscena {
public:
  Peon(bool usar_textura = false);
};

#endif
