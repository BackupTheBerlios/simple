#include "elemento.h"
#include "constantes.h"
#ifndef _temporizador_
#define _temporizador_


/*	El Temporizador es un poco especial, y por sus caracter�sticas
	no puede reaprovechar de la clase padre (ElementoSimple) tanto
	como ser�a deseable.*/
	
class Temporizador : public Elemento {
	public:
		Temporizador();
		void 	construir		(DOMNode* nodo);						
		virtual DOMElement*		getNodo();
		
		float 	getVoltajeEntradaInicial	();
		float	getVoltajeSalidaInicial		();
		float 	getVoltajeActivacion		();
		float 	getVoltajeSalidaEnTimeout	();
		float	getTiempo					();
		void 	actualizar					();
	protected:
		
		DOMElement*		getNodo(char* nombreElemento);
		
		float voltajeEntradaInicial, 	voltajeSalidaInicial;
		float voltajeActivacion,		voltajeSalidaEnTimeout;
		/*	Esta variable almacena el tiempo que tiene que esperar
			el temporizador hasta cambiar su salida*/
		unsigned int long tiempo;
		
		unsigned int long tiempoActual;
		
		/*	Aqui se almacenan los nodos XML que se 
			escribir�n cuando sea necesario*/
		DOMElement*	nodoVoltajeEntradaInicial;
		DOMElement*	nodoVoltajeSalidaInicial;
		DOMElement*	nodoVoltajeActivacion;
		DOMElement*	nodoVoltajeSalidaEnTimeout;
		DOMElement*	nodoTiempo;
		
};



#endif
