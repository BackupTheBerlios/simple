#include "temporizador.h"


Temporizador::Temporizador()
{
	tiempoActual=0;
}


/*	Se actualiza el tiempo actual y si se ha alcanzado el tiempo límite o
	timeout, se notifica a los suscriptores y se reinicializa el temporizador*/
void Temporizador::actualizar()
{
	tiempoActual++;
	
	if (tiempoActual==tiempo)
	{
		notificar();
		tiempoActual=0;
	}
}

void Temporizador::construir (DOMNode* nodo)
{
	
}
DOMElement*	Temporizador::getNodo()
{
	return Temporizador::getNodo("temporizador");
}
DOMElement* Temporizador::getNodo(char *nombreElemento)
{

}


float 	Temporizador::getVoltajeEntradaInicial	()
{
	return voltajeEntradaInicial;
}
float	Temporizador::getVoltajeSalidaInicial	()
{
	return voltajeSalidaInicial;
}
float 	Temporizador::getVoltajeActivacion		()
{
	return voltajeActivacion;
}
float 	Temporizador::getVoltajeSalidaEnTimeout	()
{
	return voltajeSalidaEnTimeout;
}
float	Temporizador::getTiempo					()
{
	return tiempo;
}
