#include "constantes.h"
#include "elemento.h"
#include "conector.h"
#include <map>
#include <string>
#ifndef _sistema_
#define _sistema_

using namespace std;

class Sistema : public Elemento
{
	public:
		Sistema();
		
		/*	En sistemas es necesario modificar la forma de añadir
			suscripciones. Consultar los detalles de implementacion
			en sistema.cpp*/
			
		int anadirSuscriptor   (Elemento* e,int pos_entrada=POS_ENTRADA, 
							int pos_salida=POS_SALIDA);
		int eliminarSuscriptor (Elemento* e,int pos_entrada=POS_ENTRADA, 
							int pos_salida=POS_SALIDA);
							
		/*	Introduce una señal en una cierta posicion del
			vector de entradas. El llamador asume la responsabilidad
			de que sea la correcta*/
		int setEntrada (Senal* s, int posicion);
		
		/* 	Este método permite modificar la señal de entrada basándonos
			en un nombre y poner esa señal en la posicion de entrada de
			ese elemento*/
		int setEntrada (Senal* s, const char* nombre, int posicion=POS_ENTRADA);
		
		/*	Incorpora un elemento al sistema */
		int anadirElemento(Elemento* e);
		
		/*	Elimina un elemento del sistema */
		int eliminarElemento (Elemento* e);
		/*	Nos devuelve la entrada de un elemento dado su nombre*/
		Senal* getEntradaPorNombre (const char* nombre);
		
		/*	Nos devuelve la salida de un elemento dado su nombre*/
		Senal* getSalidaPorNombre (const char* nombre);
		
		Elemento* getRefElementoPorNombre (const char* nombreElemento);
		
		/*	Nos devuelve la posicion que en el vector de entradas o salidas
			de un cierto elemento. Si es un elemento multientrada o multisalida
			las siguientes posiciones son las siguientes entradas*/
		int getPrimeraEntrada(const char* nombreElemento);
		int getPrimeraSalida (const char* nombreElemento);
		
		/* 	Estos metodos se redefinen aqui porque proporcionan mucha comodidad
			al no tener que sumar todo el rato POS_ENTRADA*/
		int getPrimeraEntradaUtil (const char* nombreElemento);
		int getPrimeraSalidaUtil  (const char* nombreElemento);
		
		/*	Estos metodos van a ser ligeramente redefinidos*/
		Senal* getEntradaPorPosicion(int posicion=POS_ENTRADA);
		Senal* getSalidaPorPosicion (int posicion=POS_SALIDA);
	protected:
    	Elemento* elemento[MAX_NUM_ELEMENTOS_POR_SISTEMA];
		int MaxElementos;
		Conector* conectorEntrada[MAX_LONG_VECTOR_ENTRADAS];
		Conector* conectorSalida [MAX_LONG_VECTOR_SALIDAS];
		/* 	Muy dependiente de C++. Algunos compiladores podrían no
			soportar bien el uso de maps. En ese caso hay que modificar
			la forma de encontrar la posicion de un elemento en funcion
			de su nombre */
		map<string, int> posicionDelElemento;
		
		/*	Esto es para encontrar la primera entrada en el vector de
			entradas. Recordemos que un sistema es al fin y al cabo
			un elemento*/
		map<string, int> primeraEntradaDelElemento;
		
		/*	Y esto para encontrar la primera salida*/
		map<string,	int> primeraSalidaDelElemento;
	private:
		/*	Esta funcion busca un conector en un vector de conectores
			cuya suscripcion se haya hecho con el elemento e, y avisando 
			a esa posicion*/
		int buscarConector (Conector* vector[], Elemento* e, 
				int posicion, int limMaxVector);
};
#endif
