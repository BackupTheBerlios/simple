#include "elemento.h"

#ifndef _biestable_
#define _biestable_

class Biestable: public Elemento
{
	public:
		Biestable(Voltaje* activar_r, Voltaje* desactivar_r,
			Voltaje* activar_s, Voltaje* desactivar_s,
			Voltaje* activar_Q, Voltaje* desactivar_Q, 
			Voltaje* activar_Qneg, Voltaje* desactivar_Qneg);
		int setEntrada(Senal* s, int posicion=POS_ENTRADA);
		int setReset (Voltaje* c);
		int setSet (Voltaje *c);
		
		
		/*	Metodos getter*/
		Voltaje* 	getQ();
		Voltaje* 	getQneg();
		Voltaje* 	getActivacionR();
		Voltaje* 	getActivacionS();
	protected:
		
		Voltaje* activar_R;
		Voltaje* desactivar_R;
		
		Voltaje* activar_S;
		Voltaje* desactivar_S;
		
		Voltaje* activar_Q;
		Voltaje* desactivar_Q;
		
		Voltaje* activar_Qneg;
		Voltaje* desactivar_Qneg;
		
	private:
		int obtenerValorR(Voltaje* valor_r);
		int obtenerValorS(Voltaje* valor_s);
		
};

#endif
