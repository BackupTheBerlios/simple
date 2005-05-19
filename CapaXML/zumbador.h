#include "elementos.h"
#include "constantes.h"

#ifndef _zumbador_
#define _zumbador_

class Zumbador : public Elemento {
       public:
              Zumbador();
              void 	construir (DOMNode* nodo);
              float	getEntradaReposo		();
              float getSalidaReposo			();
              float	getEntradaActivacion	();
              float	getSalidaActivacion		();
              DOMElement* getNodo			();
       private:
               /*Para un cierto magnetismo de entrada hay un voltaje
                *de salida*/
               float entradaReposo,			salidaReposo 	;
			   float entradaActivacion, 	salidaActivacion;
};

#endif
