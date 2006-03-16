#include "zumbador.h"

Zumbador::Zumbador ()
{
	Zumbador::Zumbador (NULL, NULL, NULL, NULL);
}
Zumbador::Zumbador (Voltaje* voltReposo, Frecuencia* frecReposo,
			Voltaje* voltActivacion, Frecuencia* frecActivacion)
{
	voltajeReposo			=	voltReposo;
	frecuenciaReposo		=	frecReposo;
	voltajeActivacion		=	voltActivacion;
	frecuenciaActivacion	=	frecActivacion;	
	entradas[POS_ENTRADA]	=	voltReposo;
	salidas [POS_SALIDA]	=	frecReposo;
}

Voltaje* Zumbador::getVoltajeReposo()
{
	return voltajeReposo;
}

Voltaje* Zumbador::getVoltajeActivacion()
{
	return voltajeActivacion;
}

Frecuencia*	Zumbador::getFrecuenciaReposo()
{
	return frecuenciaReposo;
}

Frecuencia*	Zumbador::getFrecuenciaActivacion()
{
	return frecuenciaActivacion;
}

int Zumbador::setEntrada (Senal* s, int posicion)
{
	Voltaje* vEntrada=(Voltaje*) s;
	
	if (vEntrada->getValor()==voltajeReposo->getValor() )
	{
		entradas[POS_ENTRADA]=vEntrada;
		salidas [POS_SALIDA] =frecuenciaReposo;
		return (Elemento::setEntrada(s, posicion));
	}
	if (vEntrada->getValor()==voltajeActivacion->getValor() )
	{
		entradas[POS_ENTRADA]=vEntrada;
		salidas [POS_SALIDA] =frecuenciaActivacion;
		return (Elemento::setEntrada(s, posicion));
	}
	
	/*	La entrada no pertenece a ningun caso conocido*/
	entradas[POS_ENTRADA]=vEntrada;
	return (Elemento::setEntrada(s,posicion));
}
