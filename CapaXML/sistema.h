#include "elementos.h"
#include "motor.h"
#include "electroiman.h"
#include "reed.h"
#include "lampara.h"
#include "pulsador.h"
#include "fotosensor.h"
#include <iostream>
#ifndef _sistema_
#define _sistema_

using namespace std;
class Sistema: public Elemento {
	public:
		Sistema 	() ;
		void		construir 			(DOMNode* nodo);
		int 		anadirRelacion 		(Relacion* r);
		int 		anadirComponente	(Elemento* e);
		int			getComponentes 		(Elemento* vectorElementos[]);
		int			getRelaciones		(Relacion* vectorRelaciones[]);	
		int			getNumComponentes	();
		int			getNumRelaciones	();
		
		/*	Estas funciones nos devuelven una referencia al
			elemento cuyo nombre sea uno de los parámetros
			o NULL en caso contrario */
		Elemento*	getRefElemento		(char* nombre);
		Elemento*	getRefElemento		(XMLCh* nombre);
	private:
		Elemento* 	listaComponentes[MAX_TAM_VECTOR];
		Relacion*	listaRelaciones [MAX_TAM_VECTOR];
		int			numComponentes, numRelaciones;
};



#endif
