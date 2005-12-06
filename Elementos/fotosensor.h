#include "elemento.h"

#ifndef _fotosensor_
#define _fotosensor_

class FotoSensor : public Elemento
{
	public:
		FotoSensor(Luminosidad* lReposo, Luminosidad* lActivacion,
			Voltaje* vReposo, Voltaje* vActivacion);
		
		/*	Metodos getter*/
		Luminosidad* getLuminosidadEntradaReposo();
		Luminosidad* getLuminosidadEntradaActivacion();
		Voltaje*	 getVoltajeSalidaReposo();
		Voltaje*	 getVoltajeSalidaActivacion();
		int			 setEntrada (Senal* v, int posicion=POS_ENTRADA);
		
	protected:
		Luminosidad* luminosidadReposo;
		Luminosidad* luminosidadActivacion;
		Voltaje*	 voltajeSalidaReposo;
		Voltaje*	 voltajeSalidaActivacion;
			
};

#endif
