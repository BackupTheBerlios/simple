#include "elementos.h"
#include "constantes.h"
#ifndef _reed_
#define _reed_

class Reed : public Elemento {
       public:
              Reed();
              void 	construir (DOMNode* nodo);
              float	getEntradaReposo		();
              float getSalidaReposo			();
              float	getEntradaActivacion	();
              float	getSalidaActivacion		();
       private:
               /*Para un cierto magnetismo de entrada hay un voltaje
                *de salida*/
               float entradaReposo,			salidaReposo 	;
			   float entradaActivacion, 	salidaActivacion;
};



#endif
