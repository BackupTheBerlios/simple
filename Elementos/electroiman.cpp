#include "electroiman.h"
#include "constantes.h"

Electroiman::Electroiman(Voltaje* vEntradaReposo, Voltaje* vEntradaActivacion,
			Magnetismo* mSalidaReposo, Magnetismo* mSalidaActivacion)
{
	voltajeEntradaReposo	=	vEntradaReposo;
	voltajeEntradaActivacion=	vEntradaActivacion;
	magSalidaReposo			=	mSalidaReposo;
	magSalidaActivacion		=	mSalidaActivacion;
	
	entradas[POS_ENTRADA]= vEntradaReposo;
	salidas [POS_SALIDA ]= mSalidaReposo;
}

Voltaje* Electroiman::getVoltajeEntradaReposo()
{
	return voltajeEntradaReposo;
}

Voltaje* Electroiman::getVoltajeEntradaActivacion()
{
	return voltajeEntradaActivacion;
}

Magnetismo* Electroiman::getMagSalidaReposo()
{
	return magSalidaReposo;
}

Magnetismo* Electroiman::getMagSalidaActivacion()
{
	return magSalidaActivacion;
}

int Electroiman::setEntrada (Senal* entrada, int posicion)
{
	Voltaje *voltEntradaActual=(Voltaje*) entrada;
	
	if (voltEntradaActual->getValor() == voltajeEntradaReposo->getValor() )
	{
		entradas[POS_ENTRADA]	=	voltajeEntradaReposo;
		salidas [POS_SALIDA] 	=	magSalidaReposo;
		return (Elemento::setEntrada (entrada,posicion) );
	}
	
	if (voltEntradaActual->getValor() == voltajeEntradaActivacion->getValor() )
	{
		entradas[POS_ENTRADA]	=	voltajeEntradaActivacion;
		salidas [POS_SALIDA] 	=	magSalidaActivacion;
		return (Elemento::setEntrada (entrada,posicion) );
	}
	 
	 /*	¡Cuidado!. Si se llega a este punto es porque la entrada, no 
	 	era válida, por lo que simplemente se toma nota de la entrada
	 	pero no se produce ninguna variacion en la salida. El problema
	 	habrá ocurrido en el llamador de esta funcion, que no ha 
	 	suministrado un valor correcto*/
	 	
	entradas[POS_ENTRADA]=voltEntradaActual;
	return (Elemento::setEntrada (entrada,posicion) );
}
