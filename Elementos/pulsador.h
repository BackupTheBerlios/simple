#include "elemento.h"

#ifndef _pulsador_
#define _pulsador_

class Pulsador: public Elemento
{
	public:
		Pulsador ();
		/* 	Cuando se conecta de la forma c1, se devuelve el voltaje v1
			y cuando se conecta de la forma c2, se devuelve el voltaje v2*/
		Pulsador(Conexion* c1, Voltaje* v1, Conexion* c2, Voltaje* v2);
		
		Conexion*	getConexionReposo();
		Conexion*	getConexionActivacion();
		Voltaje*	getVoltajeReposo();
		Voltaje*	getVoltajeActivacion();
		int			setEntrada (Senal* s, int posicion=POS_ENTRADA);
		

	protected:
		Conexion* c1;
		Conexion* c2;
		Voltaje*  v1;
		Voltaje*  v2;
};

#endif
