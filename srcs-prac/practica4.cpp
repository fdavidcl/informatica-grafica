/**********************************************************************
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
**********************************************************************/

// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 4  (implementación)
// **
// *********************************************************************

#include "aux.hpp"
#include "tuplasg.hpp"   // Tupla3f
#include "practica4.hpp"
#include "matrices-tr.hpp"
#include "MallaRev.hpp"
#include "FuenteLuz.hpp"

static NodoGrafoEscena* p4_escena = NULL;
static ColeccionFL* p4_luces = NULL;
static unsigned current_longi = 1;

void P4_Inicializar(int argc, char *argv[]) {
  p4_escena = new Escena();
  p4_luces = new ColeccionFuentesP4();
  p4_luces->activar();
}

bool P4_FGE_PulsarTeclaNormal(unsigned char tecla) {
  if (toupper(tecla) == 'G') {
    current_longi = !current_longi;
    return true;
  } else if (tecla == '<') {
    static_cast<FuenteDireccional*>(p4_luces->fuentes.at(0))->variarAngulo(current_longi, -10);
    return true;
  } else if (tecla == '>') {
    static_cast<FuenteDireccional*>(p4_luces->fuentes.at(0))->variarAngulo(current_longi, 10);
    return true;
  }

  return false;
}

void P4_DibujarObjetos(ContextoVis modo) {
  glEnable(GL_LIGHTING);

  p4_escena->visualizar(modo);

  glDisable(GL_LIGHTING);
}

Escena::Escena() {
  agregar(new Lata());

  agregar(new MaterialPeonMadera());
  agregar(MAT_Traslacion(-3, 1.4, 3));
  agregar(new Peon(true));

  agregar(new MaterialPeonBlanco());
  agregar(MAT_Traslacion(3, 0, 0));
  agregar(new Peon());

  agregar(new MaterialPeonNegro());
  agregar(MAT_Traslacion(3, 0, 0));
  agregar(new Peon());
}

Lata::Lata() {
  agregar(MAT_Escalado(4, 4, 4));

  agregar(new MaterialTapasLata());
  agregar(new BaseInfLata());
  agregar(new BaseSupLata());

  agregar(MAT_Rotacion(90, 0, 1, 0));
  agregar(new MaterialLata());
  agregar(new LateralLata());
}

LateralLata::LateralLata() {
  // La malla de revolución para el cuerpo de la lata la
  // generamos sin bases y con una textura, invirtiendo
  // el cálculo de las coordenadas de textura:
  agregar(new MallaRevol("lata-pcue.ply", 40, false, false, true, true));
}

BaseInfLata::BaseInfLata() {
  agregar(new MallaRevol("lata-pinf.ply", 40, false));
}

BaseSupLata::BaseSupLata() {
  agregar(new MallaRevol("lata-psup.ply", 40, false));
}

Peon::Peon(bool usar_textura) {
  agregar(new MallaRevol("../plys/peon.ply", 40, usar_textura));
}
