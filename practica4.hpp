#ifndef IG_PRACTICA4_HPP
#define IG_PRACTICA4_HPP

void P4_Inicializar(int argc, char *argv[]);
bool P4_FGE_PulsarTeclaNormal(unsigned char tecla);
void P4_DibujarObjetos(unsigned modo);

class Escena : public NodoGrafoEscena {

};

class Lata : public NodoGrafoEscena {
  Lata();
};

class BaseInfLata : public NodoGrafoEscena {
  BaseInfLata();
};

class BaseSupLata : public NodoGrafoEscena {
  BaseSupLata();
};

class Peon : public NodoGrafoEscena {
  Peon();
};

#endif
