#include "motor.h"
#include "constantes.h"

Motor::Motor ()
{
	this->voltajeReposo	=	NULL;
	this->giroReposo	=	NULL;
	this->voltajeGiroCW	=	NULL;
	this->giroCW		=	NULL;
	this->voltajeGiroCCW=	NULL;
	this->giroCCW		=	NULL;
	this->rpm			=	0;
	
	entradas[POS_ENTRADA]=NULL;
	salidas [POS_SALIDA] =NULL;
}
Motor::Motor (Voltaje* voltReposo,	Giro* giroReposo, 
			  Voltaje* voltGiroCW,	Giro* giroCW,
			  Voltaje* voltGiroCCW,Giro* giroCCW, unsigned int revoluciones)
{
	this->voltajeReposo	=	voltReposo;
	this->giroReposo	=	giroReposo;
	this->voltajeGiroCW	=	voltGiroCW;
	this->giroCW		=	giroCW;
	this->voltajeGiroCCW=	voltGiroCCW;
	this->giroCCW		=	giroCCW;
	this->rpm			=	revoluciones;
	
	entradas[POS_ENTRADA]=voltReposo;
	salidas [POS_SALIDA] =giroReposo;
}

Voltaje* Motor::getVoltajeReposo()
{
	return voltajeReposo;
}

Voltaje* Motor::getVoltajeGiroCW()
{
	return voltajeGiroCW;
}

Voltaje* Motor::getVoltajeGiroCCW()
{
	return voltajeGiroCCW;
}

Giro* Motor::getGiroReposo()
{
	return giroReposo;
}

Giro* Motor::getGiroCW()
{
	return giroCW;
}

Giro* Motor::getGiroCCW()
{
	return giroCCW;
}
		
unsigned int Motor::getRPM()
{
	return rpm;
}

int Motor::setEntrada(Senal* entrada, int posicion)
{
	Voltaje* voltEntrada=(Voltaje*)entrada;
	
	if (voltEntrada->getValor()==voltajeReposo->getValor())
	{
		#ifdef DEBUG_MOTOR
		printf ("Motor parado\n");
		#endif
		entradas[POS_ENTRADA]=voltEntrada;
		salidas [POS_SALIDA] =giroReposo;
		return (Elemento::setEntrada(entrada,posicion));
	}
	
	if (voltEntrada->getValor()==voltajeGiroCCW->getValor())
	{
		#ifdef DEBUG_MOTOR
		printf ("Motor gira CCW\n");
		#endif
		entradas[POS_ENTRADA]=voltajeGiroCW;
		salidas [POS_SALIDA] =giroCCW;
		return (Elemento::setEntrada(entrada,posicion));
	}
	
	if (voltEntrada->getValor()==voltajeGiroCW->getValor())
	{
		#ifdef DEBUG_MOTOR
		printf ("Motor gira CW\n");
		#endif
		entradas[POS_ENTRADA]=voltajeGiroCW;
		salidas [POS_SALIDA] =giroCW;
		return (Elemento::setEntrada(entrada,posicion));
	}
	
	/*	Entrada no contemplada*/
	entradas[POS_ENTRADA]=voltEntrada;
	return (Elemento::setEntrada(entrada,posicion));
}
