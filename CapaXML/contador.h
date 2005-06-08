#include "elementosimple.h"

#ifndef _contador_
#define _contador_

class Contador: public ElementoSimple {
	public:
		virtual DOMElement*		getNodo					();
		
		/*	Construir tiene que ser parcialmente ampliado para que tambien
			pueda leer el numero de pulsos del fichero XML*/
		virtual void 			construir 				(DOMNode* nodo);
		virtual	void 			setEntrada	 			(float entrada);
		float					getNumeroDePulsos		();
		void					reset					();
	protected:
		/*	Esta variable indica cuando debe "saltar" el contador*/
		unsigned int numeroDePulsos;
	private:
		/*	Lleva la cuenta de los pulsos que se han producido hasta ahora*/
		unsigned int contadorDePulsos;
};



#endif
