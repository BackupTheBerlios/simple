#include "pulsador.h"
#include "constantes.h"


Pulsador::Pulsador(Conexion* c1, Voltaje *v1, Conexion* c2, Voltaje* v2)
{
	this->c1=c1;
	this->c2=c2;
	this->v1=v1;
	this->v2=v2;
	entradas[POS_ENTRADA]=c1;
	salidas[POS_SALIDA]=v1;
}

Voltaje* Pulsador::getVoltajeReposo()
{
	return v1;
}

Voltaje* Pulsador::getVoltajeActivacion()
{
	return v2;
}

Conexion* Pulsador::getConexionReposo()
{
	return c1;
}

Conexion* Pulsador::getConexionActivacion()
{
	return c2;
}

int Pulsador::setEntrada(Senal* s, int posicion)
{
	/*	Si el voltaje que introducimos es el de activacion se devuelve
		por la salida correspondiente la salida */
	Conexion* c=(Conexion*) s;
#ifdef DEBUG
	printf ("-----------PULSADOR----------\n");
	printf ("La conexion pasiva es %b\n", c1->getValor());
	printf ("La conexion activa es %b\n", c2->getValor());
	printf ("El voltaje pasivo es %f\n", v1->getValor());
	printf ("El voltaje activo es %f\n", v2->getValor());	
	printf ("-----------PULSADOR----------\n");
#endif

	if ( c->getValor()==c2->getValor() )
	{
		salidas[POS_SALIDA]=v2;
		#ifdef DEBUG_PULSADOR
		printf ("Se activa el pulsador %s\n", nombreElemento);
		#endif
		return (Elemento::setEntrada((Senal*)c,posicion));
	}
	
	if ( c->getValor()==c1->getValor() )
	{
		#ifdef DEBUG_PULSADOR
		printf ("Se desactiva el pulsador %s\n", nombreElemento);
		#endif
		salidas[POS_SALIDA]=v1;
		return (Elemento::setEntrada((Senal*)c,posicion));
	}
}
