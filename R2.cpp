#include "R2.hpp"
#include "matrices-tr.hpp"
#include "practica1.hpp"
#include "MallaPly.hpp"

CabezaR2::CabezaR2(float giro, float offset) {
  color = Tupla3f(0.66, 0.66, 0.66);
  agregar(MAT_Rotacion(0, 0, 1, 0)); // Vacía (usamos el método)
  agregar(MAT_Traslacion(0, 2.48, 0));

  agregar(new Camara());

  agregar(MAT_Escalado(0.00777, 0.00777, 0.00777));
  agregar(new MallaPly("sphere.ply"));

  agregar(pr = new ProjR2(offset));

  girar(giro);
  extender(offset);
}

void CabezaR2::girar(float giro) {
  entradas.at(0) = EntradaNGE(MAT_Rotacion(-30 + 60 * giro, 0, 1, 0));
}

Camara::Camara() {
  agregar(MAT_Rotacion(-30, 1, 0, 0));
  agregar(MAT_Escalado(0.35, 0.35, 0.35));
  agregar(MAT_Traslacion(-0.5, -0.5, 1.8));
  Cubo * cuadrado = new Cubo();
  agregar(cuadrado);
  cuadrado->setColor(Tupla3f(0.08, 0.29, 0.75));

  agregar(MAT_Traslacion(0.5, 0.5, 0.75));
  agregar(MAT_Escalado(0.00368, 0.00368, 0.00368));
  MallaPly * camara = new MallaPly("sphere.ply");
  agregar(camara);
  camara->setColor(Tupla3f(0.1, 0.1, 0.1));
}

ProjR2::ProjR2(float offset) {
  color = Tupla3f(0.66, 0.66, 0.66);
  agregar(MAT_Rotacion(15, 0, 1, 0));

  agregar(MAT_Traslacion(0, 20, 120));
  agregar(MAT_Escalado(0.1, 0.1, 0.1));
  MallaPly * base_camara = new MallaPly("sphere.ply");
  agregar(base_camara);
  base_camara->setColor(Tupla3f(0.75, 0.75, 0.75));

  agregar(MAT_Rotacion(85, 1, 0, 0));
  agregar(MAT_Escalado(1, 1, 1)); // Vacío (usamos el método)
  agregar(new Cilindro(5));
  agregar(MAT_Escalado(0.9, 1.01, 0.9));
  Cilindro * interior_camara = new Cilindro(5);
  agregar(interior_camara);
  interior_camara->setColor(Tupla3f(0.2, 0.2, 0.2));
}

void ProjR2::extender(float offset) {
  entradas.at(5) = EntradaNGE(MAT_Escalado(80, 60 * offset + 80, 80));
}

CuerpoR2::CuerpoR2() {
  color = Tupla3f(0.86, 0.86, 0.9);
  agregar(MAT_Escalado(1, 1.2, 1));
  agregar(new Cilindro(5));
}

BrazoSuperior::BrazoSuperior() {
  color = Tupla3f(0.9, 0.9, 0.95);
  agregar(MAT_Rotacion(90, 0, 1, 0));
  agregar(MAT_Rotacion(90, 1, 0, 0));
  agregar(MAT_Escalado(0.4, 0.14, 0.4));
  agregar(new Cilindro(5));

  agregar(MAT_Traslacion(0, 1, 0));
  agregar(MAT_Escalado(0.7, 1, 0.7));
  Cilindro * junta = new Cilindro(5);
  agregar(junta);
  junta->setColor(Tupla3f(0.6, 0.62, 0.65));

  agregar(MAT_Traslacion(0, -1.01, 0));
  agregar(MAT_Escalado(0.5, 2, 0.5));
  Cilindro * agujero = new Cilindro(5);
  agregar(agujero);
  agujero->setColor(Tupla3f(0.2, 0.22, 0.26));
}

LadoBrazo::LadoBrazo() {
  color = Tupla3f(0.65, 0.67, 0.7);
  agregar(MAT_Traslacion(0.05, -1.5, -0.18));
  agregar(MAT_Escalado(0.2, 1.5, 0.35));
  agregar(new Cubo());

  agregar(MAT_Traslacion(-0.3, 0, 0.2));
  agregar(MAT_Escalado(1.2, 1, 0.6));
  Cubo * lateral = new Cubo();
  agregar(lateral);
  lateral->setColor(Tupla3f(0.05, 0.15, 0.35));

  agregar(MAT_Traslacion(-0.15, -0.25, -0.5));
  agregar(MAT_Escalado(1.5, 0.25, 2));
  agregar(new Cubo());
}

BrazoR2::BrazoR2(float giro, float offset) {
  // Coloca el brazo a un lado y traslada hacia arriba
  agregar(MAT_Traslacion(-1.35, 2, 0));
  agregar(MAT_Rotacion(0, 1, 0, 0)); // Vacía (giramos con el método)

  agregar(new BrazoSuperior());

  agregar(MAT_Traslacion(0, 0, 0)); // Vacía (usamos el método)
  agregar(new LadoBrazo());

  // Coloca la pata
  agregar(MAT_Rotacion(12, 1, 0, 0));
  agregar(MAT_Traslacion(0.1, -2.3, 0.4));
  agregar(new PataR2());

  girar(giro);
  extender(offset);
}

void BrazoR2::girar(float giro) {
  // Gira el brazo según el parámetro dado
  entradas.at(1) = EntradaNGE(MAT_Rotacion(60 * giro, 1, 0, 0));
}

void BrazoR2::extender(float offset) {
  // Permite extender el brazo
  entradas.at(3) = EntradaNGE(MAT_Traslacion(0, (offset - 1)/3.0, 0));
}

PataR2::PataR2() {
  color = Tupla3f(0.8, 0.8, 0.85);
  agregar(MAT_Escalado(0.3, 0.5, 0.5));
  agregar(new MallaPly("truncated_pyramid.ply"));
}

R2::R2() {
  // Coloca la pata inferior
  agregar(MAT_Traslacion(0, -0.35, 0.5));
  agregar(new PataR2());
  agregar(MAT_Traslacion(0, 0.35, -0.5));

  // Gira todo el robot para adoptar la posición típica de R2
  agregar(MAT_Rotacion(-12, 1, 0, 0));

  // Coloca la cabeza y el cuerpo
  agregar(cabeza = new CabezaR2(R2::DEFAULT_VALUE, R2::DEFAULT_VALUE));
  agregar(new CuerpoR2());

  // Coloca los dos brazos: uno al lado derecho de R2 y realizando una simetría
  // (componiendo una rotación de π y un escalado inverso) para el izquierdo
  agregar(izquierdo = new BrazoR2(R2::DEFAULT_VALUE, R2::DEFAULT_VALUE));
  agregar(MAT_Rotacion(180, 0, 1, 0));
  agregar(MAT_Escalado(1, 1, -1));
  agregar(derecho = new BrazoR2(R2::DEFAULT_VALUE, R2::DEFAULT_VALUE));

}

const float R2::DEFAULT_VALUE = 0.5;

/*
+--------------------------------------------------------------------------------+
|                                                                                |
|                                      ...~=~ ~. .....                           |
|                                  .. .~::+:~~.~~~~+=++~..                       |
|                               ..::++:.. .... ....~+======.                     |
|                             .=:++++=~  ...... ....:++++=oo+=                   |
|                           .~=+++==o=:..~~..........:+++ooooo=.                 |
|                          .:++=+=oooo+:.............~::::===ooo=.               |
|                         .:+=+==oooo+~..     ......~++~. ...:=:~..              |
|                        .~:++==oo=+::.......~:+:~~~:+~.. ....~~.. .             |
|                       ..::::+:++:::~~.~~...:=ooo:::~.....~...~... .            |
|                       .~~..~+:+::~:~~..~...~==o=:~~~..........~....            |
|                       ......+:~~::::~.......~~~...............~~~...           |
|                       .    .:~.~...........~~~~~~~::~:~~~~.~..~~~~~.           |
|                           .......~.~~~~~::::::+~.......       .  ..=.          |
|                       .   ...~~:~:::++==o=oo=oo:..~~::::+++::::::::+.          |
|                      ....~~~~:+===oooooooooooooo=++:::~:::~........~==+..      |
|                   .~=++=o=ooooooooo=ooooooo=o=oo~......~~::~~.~~~~~:+=o==.     |
|                  ~===oooooooooo++oo=ooooooo==ooo=++=+=+=o=o=++=+=====:=o=o.    |
|                 .ooooooooooooooo+:==oooooooo=o=oo===+::~~~.~....~~...~:===+.   |
|                .+=o+~~+oooooooooo::==ooooooo=oooo+.............~~+:~:+~++++.   |
|                .::=.  .+ooooooooo+~+==oooooooo=oo=:+=++++=+==o=ooooo==::::~.   |
|                .++:....~=ooo===o=+~:+=oooooo==o=ooooooooooo=:++:+~+oo=+~~~.    |
|                :~..  .~:=oo=+++++~~:+=ooooooo=oo=oooooooooo+~:....:=oo=:~..    |
|               .=~     .++:=+~::::..:++=oooooo==o=oooooooooo=::...~:=ooo:..     |
|               .=. .    .~~+:~::~~..:++===ooooo=o=ooooooooooo:+...~:+ooo=..     |
|               .=:      ..:+~~~~~..~:+++=oooooo=ooooooooooooo+~~~~~:~+oo=.      |
|                ~~ ..   ~~+:~~~~~..~:+=++=ooooo==o===+=oo=====~.~:~~~:ooo~      |
|                ..~:~  .:~+~~~~~...~:+==++ooooo==o+:::+o==oo=o::. ...+=oo+.     |
|                .::.   ::+:~~~.~. .~++===+=oooo====::~:=ooooo==~~..~~:=ooo.     |
|                 .~.  .+=:~....  ..~:++==+=ooooo==o::::=oooo=oo~~.~~::+ooo=     |
|                . :.   ~....      ..:+=====ooooo====:~~+o=ooo=o+.~~:::~=oo=.    |
|                ..~.  .~.....   ....:++====oooooo===:~::===ooo==+:++++=oooo.    |
|                .~.. .~~~.. .... ...~+=====ooooo=o==+:::==ooo=ooooooooooooo+.   |
|               . ~.. .~~.....  .....~:==o==========oo==oooooooooooooooo=ooo=.   |
|              . .~.. .:.....  ..~::++==++:+:+:+:=~+=ooooo=o=o==ooo+::.~~oooo~   |
|              .......~~....   .~::+++++++.:.:.:~:~:=ooo=+=+++++:=o+:~~.~oooo=.  |
|              =+~....~.....     :::::++=+~~:~:~:~+.+o=++::~~++::+oo~~~~:+oooo.  |
|             .oo=+:.~~......   .~++++++=+:.:.:.+.+~:=o=++++:+++::=o~~~:::=+:~.  |
|           =+::==+++:...........~++++++==+~::::+:+++=o=+===++++++=o+:+:~:...    |
|          .:=:.~+=+:~.......... .++=++=+==:::::++++==o=+=+:++::::.~~~~.~~..     |
|            =~...~++~..........  :+++++++++:::::::~~~~~~~...~~~~~.~~:~~~~..     |
|         .~==+~.+~~~........... ................ ......~~~..~~:~~~++~...        |
|       .+oooo==++=+~............    ................~.~~~~~~~~....:=+.          |
|      .ooooooo=o=:~. .~~~~......       ........... ........~.......+++.         |
|    .+oo=++=ooooo=+:. .++:~....                   ............~~~..~ ..         |
|   .ooo======o=ooo==+..:+::.....                ..~...~.~~:~..~:::~.            |
|  .~========+==oooo==+~..~..... ..            .~~~.~~~~~:::+~..:++=:.           |
|   ..~:====++==ooooo=o:..~~~.      .        .~::~::~::+:::+++:::++===           |
|     ...:+=====ooooooo=:..........         .~:::::++:++=++====++++===~          |
|        .. ~:=ooooooo=o+~~~........       . .~~:::+:+::+=++oo=========+.        |
|           ...~+=oooo===+:~..   ...         .. .~~::::++++=ooooo====o===.       |
|             ...~:+:~~~.  ....                 .. .~:::++==oooooo=====+:=.      |
|                .. ....                           ..  .~:++oooo==::~~  ..       |
|                                                      .. ~~:+:~.. ...           |
|                                                         ..  ...                |
|                                                                                |
+--------------------------------------------------------------------------------+
                                                                                */
