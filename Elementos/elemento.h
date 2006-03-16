#include "senal.h"
#include "constantes.h"
//Evitar instanciación de plantillas
#define XERCES_TMPLSINC
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/validators/common/Grammar.hpp>	
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/dom/DOMElement.hpp>


#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif	


#ifndef _elemento_
#define _elemento_


/*	Definida mas abajo*/
class Suscripcion; 


/*	Para hacer los elementos lo mas genericos posibles se han utilizado vectores
	de entradas y salidas, reservándose las primeras posiciones para las
	entradas ENABLE, RESET y KEEP. Observar el fichero de constantes.h para
	mas informacion*/
class Elemento {
	public:
	/*	Constructor: Se puede ver lo que hace en elemento.cpp*/
	Elemento();
	
	/*	Si el llamador no pone nada se modifica por defecto POS_ENTRADA,
		Se hace así porque la mayor parte de los elementos solo 
		tiene una entrada*/
	virtual int setEntrada (Senal* entrada, int posicion=POS_ENTRADA);
	
	/*	Cuando otro elemento se convierte en suscriptor de este elemento
		esta conectando una cierta entrada suya a una cierta salida nuestra.
		Tambien se usan parametros por defecto*/
	int anadirSuscriptor   (Elemento* e,int pos_entrada=POS_ENTRADA, 
							int pos_salida=POS_SALIDA);
	int eliminarSuscriptor (Elemento* e,int pos_entrada=POS_ENTRADA, 
							int pos_salida=POS_SALIDA);
	
	/*	Manipulacion del nombre del elemento */
	void setNombreElemento (char* nombre);
	/* 	Es importante que se devuelva un const char* para evitar que alguien
		modifique el nombre "desde fuera" usando el puntero */
	const char* getNombreElemento();
	
	int getTotalEntradas();
	int getTotalSalidas ();
	int getTotalSuscripciones();
	
	/* Nos dicen si una entrada o salida es un voltaje o giro de motor...*/
	int getTipoEntrada(int posicion=POS_ENTRADA);
	int getTipoSalida (int posicion=POS_SALIDA);
	
	/* Para leer las señales a la entrada y salida de un elemento*/
	Senal* getEntradaPorPosicion(int posicion=POS_ENTRADA);
	Senal* getSalidaPorPosicion (int posicion=POS_SALIDA);
	
	/*	Las primeras entradas estan reservadas para las
		entradas DEBUG, RESET y similares. Estas funciones
		nos devuelven la primera entrada "real"*/
	virtual int getPrimeraEntradaUtil();
	virtual int getPrimeraSalidaUtil();
	virtual int getPrimeraEntradaUtil(const char* nombre);
	virtual int getPrimeraSalidaUtil (const char* nombre);
	/*	Estos metodos van sobrecargados en las clases hija. Permiten
		buscar la primera entrada de un elemento dado su nombre*/
	virtual int getPrimeraEntrada(const char* nombre);
	virtual int getPrimeraSalida (const char* nombre);
	void pintarSuscripciones();
	
	/*	Esta funcion devuelve el nodo DOM que representa a un elemento*/
	DOMElement* getNodo();
	
	/* 	Esta funcion rellena los valores del elemento con
		los que se encuentren en un nodo XML */
	void construir (DOMNode*);
	protected:
		void notificar();
		char nombreElemento[MAX_LONG_NOMBRE_ELEMENTO];
		Senal* entradas[MAX_LONG_VECTOR_ENTRADAS];
		Senal* salidas [MAX_LONG_VECTOR_SALIDAS];
		Suscripcion* suscripciones[MAX_SUSCRIPCIONES];
		/*	Cada elemento tendra que indicar en su constructor cuantas
			entradas y salidas tiene*/
		int totalEntradas;
		int totalSalidas;
		int totalSuscripciones;
		
		/* 	Esta funcion nos dice si dos float son razonablemente
			iguales. Es necesaria porque en C 5.0 y 5.0000 pueden
			ser ligeramente diferentes en su mantisa y su comparacion
			con == podria dar FALSE*/
		bool iguales(float x, float y);
		
		/*	Esta funcion borra una suscripcion reordenando el vector para
			que no haya elementos NULL entre las posiciones del vector*/
		void borrarSuscripcion (int posicion);
		
};
/*	Fin de la clase Elemento*/



/*	Una suscripción queda determinada por el elemento que hace la suscripcion
	el elemento al que se suscribe y que le avisa, la posicion de la salida del
	avisador que está escuchando y la entrada del suscriptor a la que va 
	conectada
	
	Se ha dejado como clase y no como estructura en previsión 
	de futuros cambios
	
	El tomar nota del elemento avisador no es muy necesario ya que cada
	elemento que avise se conoce a si mismo y solo necesitaria conocer
	a los elementos suscritos a él pero en previsión de ampliaciones
	se ha decidido dejar la estructura asi*/
class Suscripcion
{
	public:
		/*	Metodos getter */
		Elemento* getElementoSuscriptor() 	{ return elementoSuscriptor; }
		Elemento* getElementoAvisador  () 	{ return elementoAvisador;   }
		int		  getPosEntradaSuscriptor ()	{ return entradaSuscriptor;  }
		int		  getPosSalidaAvisador	  () 	{ return salidaAvisador;	   }
		
		/*	Metodos setter */
		int setElementoSuscriptor (Elemento* e)
		{
			if (e==NULL) return -1;
			elementoSuscriptor=e;
			return 0;
		}
		
		int  setElementoAvisador (Elemento *e)
		{
			if (e==NULL) return -1;
			elementoAvisador=e;
			return 0;
		}
		
		int setEntradaSuscriptor (int entrada)
		{
			if ( (entrada<0) || (entrada>MAX_LONG_VECTOR_ENTRADAS) ) 
				return -1;
			entradaSuscriptor=entrada;
			return 0;
		}
		
		int setSalidaAvisador (int salida)
		{
			if ( (salida<0) || (salida>MAX_LONG_VECTOR_SALIDAS) ) 
				return -1;
			salidaAvisador=salida;
			return 0;
		}
		void construir (DOMNode* nodo)
		{
		}
	
	private:
		Elemento* elementoSuscriptor;
		Elemento* elementoAvisador;
		int entradaSuscriptor;
		int salidaAvisador;
};








#endif
