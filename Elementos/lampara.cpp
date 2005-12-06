#include "lampara.h"
#include "constantes.h"

Lampara::Lampara(Voltaje* v1, Luminosidad* l1, Voltaje* v2, Luminosidad* l2)
{
	this->v1=v1;
	this->v2=v2;
	this->l1=l1;
	this->l2=l2;	
	entradas[POS_ENTRADA] = v1;
	salidas [POS_SALIDA]  = l1;
}

Voltaje* Lampara::getVoltajeReposo()
{
	return v1;
}

Voltaje* Lampara::getVoltajeActivacion()
{
	return v2;
}

Luminosidad* Lampara::getLuminosidadReposo()
{
	return l1;
}

Luminosidad* Lampara::getLuminosidadActivacion()
{
	return l2;
}

int	Lampara::setEntrada (Senal* s, int posicion)
{
	Voltaje* v=(Voltaje*) s;
#ifdef DEBUG_LAMPARA
	printf ("El voltaje recibido es %f\n", v->getValor() );
#endif
	if (v2->getValor()==v->getValor() )
	{
#ifdef DEBUG_LAMPARA
		printf ("Activo la lampara\n");
#endif

		salidas[POS_SALIDA]=l2;
		return (Elemento::setEntrada( (Senal*)v, posicion ));
	}
	if (v1->getValor()==v->getValor() )
	{
#ifdef DEBUG_LAMPARA
		printf ("Desactivo la lampara\n");
#endif
		salidas[POS_SALIDA]=l1;
		return (Elemento::setEntrada( (Senal*)v, posicion ));
	}
}
