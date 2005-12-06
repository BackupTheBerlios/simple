#include "elemento.h"

#ifndef _rele_
#define _rele_

class Rele: public Elemento
{
	public:
		Rele(Voltaje* v1,Conexion* c1, Voltaje* v2, Conexion* c2);
		
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
