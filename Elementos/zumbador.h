#include "elemento.h"

#ifndef _zumbador_
#define _zumbador_

class Zumbador: public Elemento
{
	public:
		Zumbador (Voltaje* voltReposo, Frecuencia* frecReposo,
			Voltaje* voltActivacion, Frecuencia* frecActivacion);
		
		int setEntrada (Senal* s, int posicion=POS_ENTRADA);
		/*	Metodos getter */
		
		Voltaje*	getVoltajeReposo();
		Voltaje*	getVoltajeActivacion();
		Frecuencia*	getFrecuenciaReposo();
		Frecuencia*	getFrecuenciaActivacion();
		
	protected:
		Voltaje*	voltajeReposo;
		Frecuencia*	frecuenciaReposo;
		Voltaje*	voltajeActivacion;
		Frecuencia*	frecuenciaActivacion;	
};


#endif
