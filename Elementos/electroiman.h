#include "elemento.h"

#ifndef _electroiman_
#define _electroiman_

class Electroiman : public Elemento
{
	public:
		Electroiman ();
		Electroiman(Voltaje* vEntradaReposo, Voltaje* vEntradaActivacion,
			Magnetismo* mSalidaReposo, Magnetismo* mSalidaActivacion);
		
		int setEntrada (Senal* entrada, int posicion=POS_ENTRADA);
		
		/*	Metodos getter*/
		Voltaje*	getVoltajeEntradaReposo();
		Voltaje*	getVoltajeEntradaActivacion();
		Magnetismo* getMagSalidaReposo();
		Magnetismo* getMagSalidaActivacion();	
		
	protected:
		Voltaje*	voltajeEntradaReposo;
		Voltaje*	voltajeEntradaActivacion;
		Magnetismo* magSalidaReposo;
		Magnetismo* magSalidaActivacion;	
};

#endif
