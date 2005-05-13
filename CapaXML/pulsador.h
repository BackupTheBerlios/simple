#include "elementos.h"
#include "constantes.h"
#ifndef _pulsador_
#define _pulsador_

class Pulsador: public Elemento {
      public:
             Pulsador ();
             void construir (DOMNode* nodo);
             float getEntradaReposo 	();
             float getSalidaReposo		();
             float getEntradaActivacion	();
             float getSalidaActivacion	();
             void  setEntrada(float entrada);
      private:
              float entradaReposo, 		salidaReposo 		;
              float entradaActivacion, 	salidaActivacion	;
};

#endif
