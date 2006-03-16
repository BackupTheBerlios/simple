#include "elemento.h"

#ifndef _motor_
#define _motor_

class Motor: public Elemento
{
	public:
		Motor ();
		Motor (Voltaje* voltReposo,	Giro* giroReposo, 
			   Voltaje* voltGiroCW,	Giro* giroCW,
			   Voltaje* voltGiroCCW,Giro* giroCCW, unsigned int revoluciones);
		int setEntrada (Senal* entrada, int posicion=POS_ENTRADA);
		
		/*	Metodos getter*/
		Voltaje* getVoltajeReposo();
		Voltaje* getVoltajeGiroCW();
		Voltaje* getVoltajeGiroCCW();
		
		Giro* getGiroReposo();
		Giro* getGiroCW();
		Giro* getGiroCCW();
		
		unsigned int getRPM();
		
	protected:
		Voltaje* 	voltajeReposo;
		Giro*		giroReposo;
		/*	El motor puede girar en sentido de las agujas del reloj (ClockWise)
			o en sentido antihorario (CounterClockWise)*/
		Voltaje*	voltajeGiroCW;
		Giro*		giroCW;
		Voltaje*	voltajeGiroCCW;
		Giro*		giroCCW;
		/*Velocidad de giro del motor*/
		unsigned int rpm; 
		
};

#endif
