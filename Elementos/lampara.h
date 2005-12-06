#include "elemento.h"

#ifndef _lampara_
#define _lampara_

class Lampara : public Elemento
{
	public:
		Lampara (Voltaje* v1, Luminosidad* l1, Voltaje* v2, Luminosidad* l2);	
	
		Voltaje*		getVoltajeReposo();
		Voltaje*		getVoltajeActivacion();
		Luminosidad*	getLuminosidadReposo();
		Luminosidad*	getLuminosidadActivacion();
		int				setEntrada (Senal* v, int posicion=POS_ENTRADA);
	
	protected:
		Voltaje* 	 v1;
		Voltaje* 	 v2;
		Luminosidad* l1;
		Luminosidad* l2;
};

#endif
