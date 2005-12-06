#include "elemento.h"

#ifndef _suscripcion_
#define _suscripcion_


/*	Una suscripción queda determinada por el elemento que hace la suscripcion
	el elemento al que se suscribe y que le avisa, la posicion de la salida del
	avisador que está escuchando y la entrada del suscriptor a la que va 
	conectada
	
	Se ha dejado como clase y no como estructura en previsión 
	de futuros cambios
	
	El tomar nota del elemento avisador no es muy necesario ya que cada
	elemento que avise se conoce a si mismo y solo necesitaria conocer
	a los elementos suscritos a él pero en previsión de ampliaciones
	se ha decidido dejar la estructura asi*/
class Suscripcion
{
	Elemento* elementoSuscriptor;
	Elemento* elementoAvisador;
	int entrada;
	int salida;
};

#endif
