/*	Declaracion de la clase ElementoSimple
	Creada para factorizar comportamiento común a muchos elementos
	relativamente simples (pulsadores, electroimanes...) y mantener el 
	código (que puede ser bastante complejo) en un solo sitio y facilitar
	así el cambio*/


#include "elementos.h"

#ifndef	_elementosimple_
#define _elementosimple_
class ElementoSimple: public Elemento 
{
	public:
		ElementoSimple();
		virtual void 	construir 				(DOMNode* nodo);
		float			getEntradaReposo		();
		float			getSalidaReposo 		();
		float			getEntradaActivacion	();
		float			getSalidaActivacion 	();
		void			setEntrada 				(float entrada);
		
		/* Se reimplementará parcialmente en las clases hija*/
		virtual DOMElement*		getNodo			(char *nombreElemento);
		
	protected:
		float entradaReposo, 		salidaReposo ;
		float entradaActivacion,	salidaActivacion ;	
		
		/*	doc representa el documento XML que almacena un
			elemento concreto*/
		DOMDocument* doc;
		DOMElement* nodoEntradaReposo;
		DOMElement* nodoSalidaReposo;
		DOMElement*	nodoEntradaActivacion,;
		DOMElement* nodoSalidaActivacion;
};

#endif
