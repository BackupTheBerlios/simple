#include "constantes.h"
#include "rele.h"

Rele::Rele(Voltaje* v1,Conexion* c1, Voltaje* v2, Conexion* c2)
{
	this->c1=c1;
	this->c2=c2;
	this->v1=v1;
	this->v2=v2;
	entradas[POS_ENTRADA]=v1;
	salidas[POS_SALIDA]=c1;
}

Voltaje* Rele::getVoltajeReposo()
{
	return v1;
}

Voltaje* Rele::getVoltajeActivacion()
{
	return v2;
}

Conexion* Rele::getConexionReposo()
{
	return c1;
}

Conexion* Rele::getConexionActivacion()
{
	return c2;
}

int Rele::setEntrada(Senal* s, int posicion)
{
	/*	Si el voltaje que introducimos es el de activacion se devuelve
		por la salida correspondiente la salida */
	Voltaje* vEntrada=(Voltaje*) s;
	if ( vEntrada->getValor()==v2->getValor() )
	{
		salidas[POS_SALIDA]=c2;
		return (Elemento::setEntrada(s,posicion));
	}
	
	if ( vEntrada->getValor()==v1->getValor() )
	{
		salidas[POS_SALIDA]=c1;
		return (Elemento::setEntrada(s,posicion));
	}
}
