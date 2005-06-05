#include "elementosimple.h"
#include "constantes.h"
#ifndef _temporizador_
#define _temporizador_

class Temporizador : public ElementoSimple {
	public:
		/*	El constructor tiene que especificar cuando debe
			saltar el temporizador*/
		Temporizador (unsigned int tiempo);
		void 	construir		(DOMNode* nodo);						
		virtual DOMElement*		getNodo();
	protected:
		float voltajeEntradaInicial, 	voltajeSalidaInicial;
		float voltajeActivacion,		voltajeSalidaEnTimeout;
		/*	Esta variable almacena el tiempo que tiene que esperar
			el temporizador hasta cambiar su salida*/
		unsigned int long tiempo;
};



#endif
