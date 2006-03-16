#include "contador.h"


Contador::Contador ()
{
	voltajeEntradaReposo		=	NULL;
	voltajeEntradaActivacion	=	NULL;
	voltajeSalidaReposo			=	NULL;
	voltajeSalidaActivacion		=	NULL;
	
	this->autoReset=false;
	
	this->maxPulsos=-1;

	cuentaPulsos=0;
	
	entradas[POS_ENTRADA]=NULL;
	salidas [POS_SALIDA] =NULL;
}
Contador::Contador(unsigned int maxPulsos,Voltaje *v_e_reposo,
			Voltaje* v_e_activacion, Voltaje* v_s_reposo, 
			Voltaje* v_s_activacion, bool autoReset)
{
	voltajeEntradaReposo		=	v_e_reposo;
	voltajeEntradaActivacion	=	v_e_activacion;
	voltajeSalidaReposo			=	v_s_reposo;
	voltajeSalidaActivacion		=	v_s_activacion;
	
	this->autoReset=autoReset;
	
	this->maxPulsos=maxPulsos;

	cuentaPulsos=0;
	
	entradas[POS_ENTRADA]=voltajeEntradaReposo;
	salidas [POS_SALIDA] =voltajeSalidaReposo;
}

int Contador::setEntrada (Senal* s, int posicion)
{
	Voltaje* nuevaEntrada=(Voltaje*) s;
	/*	Si estan introduciendo una activacion en la posicion de reset se resetea
		la cuenta */
	if (posicion==POS_RESET)
	{
		if (nuevaEntrada->getValor()==voltajeEntradaActivacion->getValor())
		{
			cuentaPulsos=0;
			entradas[posicion]=nuevaEntrada;
			return 0;
		}
	}
	
	/*	Si por el contrario introducen algo en la entrada se examina
		la situacion*/
	if (posicion==POS_ENTRADA)
	{
		Voltaje *entradaActual=(Voltaje*) entradas[posicion];
		/*	Si lo que habia en la entrada era un "reposo" y se introduce
			una "activacion" actualizamos la cuenta de pulsos*/
		if ( (entradaActual->getValor()==voltajeEntradaReposo->getValor() ) && 
			(nuevaEntrada->getValor()==voltajeEntradaActivacion->getValor() ) )
		{
			entradas[posicion]=nuevaEntrada;
			cuentaPulsos++;
#ifdef DEBUG_CONTADOR
			printf ("Contador actualoizado\n");
#endif		
			/*	Y si se ha llegado a la cuenta total se pone en la salida
				el valor correspondiente*/
			if (cuentaPulsos==maxPulsos)
			{
#ifdef DEBUG_CONTADOR
				printf ("Contador disparado!\n");
#endif
				salidas[POS_SALIDA]=voltajeSalidaActivacion;
				
				if (autoReset)
				{
					cuentaPulsos=0;
				}
				return (Elemento::setEntrada(s, posicion) );
			}
		}
		return (Elemento::setEntrada(s, posicion) );
	}
}
int Contador::getNumPulsos()
{
	return cuentaPulsos;
}

int Contador::getMaxPulsos()
{
	return maxPulsos;
}

void Contador::reset()
{
	
}

Voltaje* Contador::getVoltajeEntradaReposo()
{
	return voltajeEntradaReposo;
}

Voltaje* Contador::getVoltajeEntradaActivacion()
{
	return voltajeEntradaActivacion;
}

Voltaje* Contador::getVoltajeSalidaReposo()
{
	return voltajeSalidaReposo;
}

Voltaje* Contador::getVoltajeSalidaActivacion()
{
	return voltajeSalidaActivacion;
}
