#include "reed.h"
#include "constantes.h"

Reed::Reed (Magnetismo *mReposo, Conexion *aReposo,
	Magnetismo *mActivacion, Conexion *aActivacion)
{
	/*	Se copian los parametros fundamentales*/
	magReposo		=	mReposo;
	magActivacion	=	mActivacion;
	conReposo		=	aReposo;
	conActivacion	=	aActivacion;
	
	entradas[POS_ENTRADA] = mReposo;
	salidas [POS_SALIDA ] = aReposo;
}

Magnetismo* Reed::getMagnetismoReposo()
{
	return magReposo;
}

Magnetismo* Reed::getMagnetismoActivacion()
{
	return magActivacion;
}

Conexion* Reed::getConexionReposo()
{
	return conReposo;
}

Conexion* Reed::getConexionActivacion()
{
	return conActivacion;
}

int Reed::setEntrada (Senal* entrada, int posicion)
{
	Magnetismo* magEntrada=(Magnetismo*) entrada;
	
	if (magEntrada->getValor() == magReposo->getValor() )
	{
		entradas[POS_ENTRADA]	=	magReposo;
		salidas [POS_SALIDA]	=	conReposo;
		return (Elemento::setEntrada(entrada,posicion) );	
	}
	
	if (magEntrada->getValor() == magActivacion->getValor() )
	{
		entradas[POS_ENTRADA]	=	magActivacion;
		salidas [POS_SALIDA]	=	conActivacion;
		return (Elemento::setEntrada(entrada,posicion) );
	}
	
	/*	¡Entrada probablemente invalida!*/
	entradas[POS_ENTRADA]=magEntrada;
	return (Elemento::setEntrada(entrada,posicion));
}
