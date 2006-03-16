#include "fotosensor.h"
#include "constantes.h"

FotoSensor::FotoSensor ()
{
	luminosidadReposo		=	NULL;
	luminosidadActivacion	=	NULL;
	voltajeSalidaReposo		=	NULL;
	voltajeSalidaActivacion	=	NULL;
	
	entradas[POS_ENTRADA]=NULL;
	salidas [POS_SALIDA] =NULL;
}
FotoSensor::FotoSensor(Luminosidad* lReposo, Luminosidad* lActivacion,
			Voltaje* vReposo, Voltaje* vActivacion)
{
	luminosidadReposo		=	lReposo;
	luminosidadActivacion	=	lActivacion;
	voltajeSalidaReposo		=	vReposo;
	voltajeSalidaActivacion	=	vActivacion;
	
	entradas[POS_ENTRADA]=lReposo;
	salidas [POS_SALIDA] =vReposo;
}

Luminosidad* FotoSensor::getLuminosidadEntradaReposo()
{
	return luminosidadReposo;
}

Luminosidad* FotoSensor::getLuminosidadEntradaActivacion()
{
	return luminosidadActivacion;
}

Voltaje* FotoSensor::getVoltajeSalidaReposo()
{
	return voltajeSalidaReposo;
}

Voltaje* FotoSensor::getVoltajeSalidaActivacion()
{
	return voltajeSalidaActivacion;
}

int	FotoSensor::setEntrada (Senal* v, int posicion)
{
	Luminosidad *lEntrada=(Luminosidad*) v;
	
	int codComparacion=strcmp (lEntrada->getValor(), 
		luminosidadActivacion->getValor() );
	bool esLuminosidadDeActivacion=(codComparacion==0);
	
	if (esLuminosidadDeActivacion)
	{
		salidas[POS_SALIDA]=voltajeSalidaActivacion;
		
	}
	else {
		salidas[POS_SALIDA]=voltajeSalidaReposo;
	}
	return (Elemento::setEntrada(v, posicion));
}
