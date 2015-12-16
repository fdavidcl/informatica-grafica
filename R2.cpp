#include "R2.hpp"
#include "matrices-tr.hpp"
#include "practica1.hpp"

CabezaR2::CabezaR2(float giro, float offset_cam)
  :giro(giro), offset_cam(offset_cam) {
}

CuerpoR2::CuerpoR2() {
  color = Tupla3f(0.9, 0.86, 0.86);
  agregar(MAT_Escalado(1, 1.2, 1));
  agregar(MAT_Rotacion(-12, 1, 0, 0));
  agregar(new Cilindro(5));
}

BrazoSuperior::BrazoSuperior() {
  color = Tupla3f(0.95, 0.9, 0.9);
  agregar(MAT_Rotacion(90, 0, 1, 0));
  agregar(MAT_Rotacion(90, 1, 0, 0));
  agregar(MAT_Escalado(0.4, 0.12, 0.4));
  agregar(new Cilindro(5));
}

LadoBrazo::LadoBrazo() {
  color = Tupla3f(0.7, 0.65, 0.65);
  agregar(MAT_Escalado(0.2, 1.4, 0.25));
  agregar(new Cubo());
}

BrazoR2::BrazoR2(float giro, float offset)
  :giro(giro), offset(offset) {
  agregar(MAT_Rotacion(giro, 1, 0, 0));
  agregar(MAT_Traslacion(0, 2, -0.2));
  agregar(new BrazoSuperior());
  agregar(MAT_Traslacion(0, offset, 0));
  agregar(new LadoBrazo());
  agregar(new PataR2());
}

PataR2::PataR2() {

}

R2::R2() {
  agregar(new CabezaR2(0, 0));
  agregar(new CuerpoR2());
  agregar(new PataR2());
  agregar(MAT_Traslacion(-1, 0, 0));
  agregar(new BrazoR2(0, 0));
  agregar(MAT_Traslacion(1.8, 0, 0));
  agregar(new BrazoR2(0, 0));
}
