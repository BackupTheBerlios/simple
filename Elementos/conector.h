#include "constantes.h"
#include "elemento.h"

#ifndef _conector_
#define _conector_

/*	Un conector es un elemento que no tiene nada de especial, se dedica
	solamente a propagar señales, de forma que la señal que recibe de
	entrada la pone en su salida*/
class Conector : public Elemento
{
	public:
		Conector();
		int setEntrada (Senal *s, int posicion=POS_ENTRADA);	
		void actualizar();
		
		/*	Los conectores solo hacen UNA conexion por lo que es
			util disponer de estos metodos tambien aqui*/
		Elemento* getElementoSuscriptor() { 
			return suscripciones[0]->getElementoSuscriptor(); 
		}
		Elemento* getElementoAvisador  () { 
			return suscripciones[0]->getElementoAvisador();   }
		int		  getPosEntradaSuscriptor () { 
			return suscripciones[0]->getPosEntradaSuscriptor();  }
		int		  getPosSalidaAvisador	   () { 
			return suscripciones[0]->getPosSalidaAvisador();	   }
};

#endif
