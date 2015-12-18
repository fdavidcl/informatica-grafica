#include "R2.hpp"
#include "matrices-tr.hpp"
#include "practica1.hpp"
#include "MallaPly.hpp"

CabezaR2::CabezaR2(float giro, float offset_cam)
  :giro(giro), offset_cam(offset_cam) {
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
  agregar(MAT_Traslacion(0.05, -1.45, -0.18));
  agregar(MAT_Escalado(0.2, 1.4, 0.35));
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

BrazoR2::BrazoR2(float giro, float offset)
  :giro(giro), offset(offset) {

  // Coloca el brazo a un lado
  agregar(MAT_Traslacion(-1.35, 0, 0));

  // Gira el brazo según el parámetro dado
  agregar(MAT_Rotacion(giro, 1, 0, 0));

  // Traslada hacia arriba
  agregar(MAT_Traslacion(0, 2, 0));
  agregar(new BrazoSuperior());

  // Permite extender el brazo
  agregar(MAT_Traslacion(0, offset, 0));
  agregar(new LadoBrazo());

  // Coloca la pata
  agregar(new PataR2());
}

PataR2::PataR2() {
  agregar(new MallaPly("truncated_pyramid.ply"));
}

R2::R2() {
  // Gira todo el robot para adoptar la posición típica de R2
  agregar(MAT_Rotacion(-12, 1, 0, 0));

  // Coloca la cabeza y el cuerpo
  agregar(new CabezaR2(0, 0));
  agregar(new CuerpoR2());

  // Coloca la pata inferior
  agregar(new PataR2());

  // Coloca los dos brazos: uno al lado derecho de R2 y realizando una simetría
  // (componiendo una rotación de π y un escalado inverso) para el izquierdo
  agregar(new BrazoR2(0, 0));
  agregar(MAT_Rotacion(180, 0, 1, 0));
  agregar(MAT_Escalado(1, 1, -1));
  agregar(new BrazoR2(0, 0));
}


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
