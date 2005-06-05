#include "elementosimple.h"
#include "constantes.h"
#ifndef _temporizador_
#define _temporizador_

class Temporizador : public ElementoSimple {
	public:
		void 	construir		(DOMNode* nodo);						
		virtual DOMElement*		getNodo();
	protected:
		
		DOMElement*		getNodo(char* nombreElemento);
		
		float voltajeEntradaInicial, 	voltajeSalidaInicial;
		float voltajeActivacion,		voltajeSalidaEnTimeout;
		/*	Esta variable almacena el tiempo que tiene que esperar
			el temporizador hasta cambiar su salida*/
		unsigned int long tiempo;
		
		/*	Aqui se almacenan los nodos XML que se 
			escribirán cuando sea necesario*/
		DOMElement*	nodoVoltajeEntradaInicial;
		DOMElement*	nodoVoltajeSalidaInicial;
		DOMElement*	nodoVoltajeActivacion;
		DOMElement*	nodoVoltajeSalidaEnTimeout;
		DOMElement*	nodoTiempo;
		
};



#endif
