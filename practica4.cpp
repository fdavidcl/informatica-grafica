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
  p4_escena->visualizar(modo);

}

Escena::Escena() {
  agregar(new Lata());
  agregar(MAT_Traslacion(-3, 1.4, 3));
  agregar(new MaterialPeonMadera());
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
  agregar(new MaterialLata());
  agregar(new LateralLata());
  agregar(new MaterialTapasLata());
  agregar(new BaseInfLata());
  agregar(MAT_Traslacion(0, 0.025, 0));
  agregar(new BaseSupLata());
}

LateralLata::LateralLata() {
  agregar(new MallaRevol("../plys/lata-pcue.ply", 20, true));
}

BaseInfLata::BaseInfLata() {
  agregar(new MallaRevol("../plys/lata-pinf.ply", 20, false));
}

BaseSupLata::BaseSupLata() {
  agregar(new MallaRevol("../plys/lata-psup.ply", 20, false));
}

Peon::Peon(bool usar_textura) {
  agregar(new MallaRevol("../plys/peon.ply", 20, usar_textura));
}
