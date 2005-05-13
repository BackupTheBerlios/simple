#include "elementos.h"

#ifndef _lampara_
#define _lampara_

class Lampara: public Elemento {
	public:
		Lampara ();
		void 	construir 				(DOMNode* nodo);
		float	getEntradaReposo		();
		float	getSalidaReposo			();
		float 	getEntradaActivacion	();
		float	getSalidaActivacion		();
		XMLCh*	getColor				();
		void  	setEntrada				(float entrada);
	private:
		float entradaReposo, 		salidaReposo 		;
		float entradaActivacion,  	salidaActivacion   	;	
		XMLCh* color;	
};



#endif
