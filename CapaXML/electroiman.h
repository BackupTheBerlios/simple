#include "elementos.h"
#ifndef _electroiman_
#define _electroiman_
class Electroiman: public Elemento {
	public:
		Electroiman () ;
		void construir (DOMNode* nodo);
		float	getEntradaReposo		();
		float	getSalidaReposo			();
		float 	getEntradaActivacion	();
		float	getSalidaActivacion		();
	private:
		float entradaReposo, 		salidaReposo ;
		float entradaActivacion,	salidaActivacion ;	
};

#endif
