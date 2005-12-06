#include "elemento.h"

#ifndef _suscripcion_
#define _suscripcion_


/*	Una suscripci�n queda determinada por el elemento que hace la suscripcion
	el elemento al que se suscribe y que le avisa, la posicion de la salida del
	avisador que est� escuchando y la entrada del suscriptor a la que va 
	conectada
	
	Se ha dejado como clase y no como estructura en previsi�n 
	de futuros cambios
	
	El tomar nota del elemento avisador no es muy necesario ya que cada
	elemento que avise se conoce a si mismo y solo necesitaria conocer
	a los elementos suscritos a �l pero en previsi�n de ampliaciones
	se ha decidido dejar la estructura asi*/
class Suscripcion
{
	Elemento* elementoSuscriptor;
	Elemento* elementoAvisador;
	int entrada;
	int salida;
};

#endif
