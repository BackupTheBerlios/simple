#include "conector.h"
#include "constantes.h"

Conector::Conector()
{
	strcpy (nombreElemento, "Conector");
}
int Conector::setEntrada (Senal* s, int entrada)
{
	entradas[entrada]=s;
	salidas[POS_SALIDA]=s;
	//printf ("Se activa el conector con una señal %s\n", s->toString() );
	return (Elemento::setEntrada(s, entrada));	
}

void Conector::actualizar()
{
	notificar();
}
