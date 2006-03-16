#include "elemento.h"
#include "constantes.h"

#ifndef _contador_
#define _contador_

/*	Esta clase implementa un contador. El funcionamiento consiste en que
	al crear un contador hay que indicar el numero de pulsos que debe contar.
	El contador tiene una entrada y va contando los cambios que se producen
	de voltajeReposo a VoltajeActivacion. Cuando el numero de cambios o
	flancos alcance la cuenta maxima la salida cambia de voltajeSalidaReposo
	a VoltajeSalidaActivacion. Si está activo el "autoreset" el contador
	se resetea automáticamente */
class Contador: public Elemento
{
	public:
		Contador ();
		Contador (unsigned int maxPulsos,Voltaje *v_e_reposo,
			Voltaje* v_e_activacion, Voltaje* v_s_reposo, 
			Voltaje* v_s_activacion, bool autoReset=false);
		int setEntrada (Senal* s, int posicion=POS_ENTRADA);
		void reset();
		
		/*	Métodos getter*/
		int getNumPulsos();
		int getMaxPulsos();
		Voltaje* getVoltajeEntradaReposo();
		Voltaje* getVoltajeSalidaReposo();
		Voltaje* getVoltajeEntradaActivacion();
		Voltaje* getVoltajeSalidaActivacion();
		
	protected:
		Voltaje* voltajeEntradaReposo;
		Voltaje* voltajeEntradaActivacion;
		Voltaje* voltajeSalidaReposo;
		Voltaje* voltajeSalidaActivacion;
		bool	 autoReset;
		int cuentaPulsos, maxPulsos;
	
	
};

#endif
