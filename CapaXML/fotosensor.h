#include "elementos.h"
#include "constantes.h"

#ifndef _fotosensor_
#define _fotosensor_

class FotoSensor: public Elemento {
	public:
		FotoSensor ();
		void 	construir (DOMNode* nodo);
		float	getEntradaReposo		();
        float 	getSalidaReposo			();
        float	getEntradaActivacion	();
        float	getSalidaActivacion		();
	private:
		float entradaReposo, 		salidaReposo 		;
        float entradaActivacion, 	salidaActivacion	;
};


#endif
