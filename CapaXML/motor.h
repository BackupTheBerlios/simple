#include "elementos.h"
#ifndef _motor_
#define _motor_

class Motor: public Elemento {
	public:
		Motor 	();
		~Motor 	();
		void 			construir 		(DOMNode* nodo);
		float			getEntradaGiro1	() const;						
		float			getEntradaGiro2	() const;
		float			getEntradaReposo() const;
		XMLCh*			getSalidaGiro1	() const;
		XMLCh*			getSalidaGiro2	() const;
		XMLCh*			getSalidaReposo	() const;
		DOMElement* 	getNodo 		() ;
	private:
		float 	entradaGiro1	;
		XMLCh*	salidaGiro1 	; 
		float 	entradaGiro2	;
		XMLCh*	salidaGiro2 	;
		float 	entradaReposo	;
		XMLCh*	salidaReposo  	;
};


#endif
