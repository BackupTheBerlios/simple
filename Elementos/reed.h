#include "elemento.h"

#ifndef _reed_
#define _reed_

class Reed: public Elemento
{
	public:
		Reed ();
		Reed (Magnetismo *mReposo, Conexion* cReposo,
			Magnetismo *mActivacion, Conexion* cActivacion);
		int	setEntrada (Senal* v, int posicion=POS_ENTRADA);	
		
		/*	Metodos getter */
		
		Magnetismo* getMagnetismoReposo();
		Magnetismo* getMagnetismoActivacion();
		Conexion*	getConexionReposo();
		Conexion*	getConexionActivacion();

	protected:
		Magnetismo *magReposo;
		Conexion   *conReposo;
		Magnetismo *magActivacion;
		Conexion   *conActivacion;
			
};

#endif
