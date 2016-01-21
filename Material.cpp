#include "Material.hpp"

//--------------------------------------------------
// Activación de materiales
void MaterialEstandar::activar() {

}

//--------------------------------------------------
// Gestión de texturas
void Textura::activar() {

}

Textura::Textura(const std::string& archivoJPG) {
  img = new jpg::Imagen(archivoJPG);
}

//--------------------------------------------------
// Materiales concretos

MaterialLata::MaterialLata() {

}

MaterialTapasLata::MaterialTapasLata() {

}

MaterialPeonMadera::MaterialPeonMadera() {

}

MaterialPeonBlanco::MaterialPeonBlanco() {

}

MaterialPeonNegro::MaterialPeonNegro() {

}
