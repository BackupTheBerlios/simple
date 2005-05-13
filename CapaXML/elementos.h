/*Fichero elementos.h
 *
 *Contiene las declaraciones de clase de los elementos que intervienen
 *en un proyecto*/
 
//Evitar instanciación de plantillas
#define XERCES_TMPLSINC

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <vector>

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif	

/*Como máximo un elemento puede tener 50 elementos a la escucha*/
#define MAX_SUSCRIPTORES 50

/*El nombre de un elemento no puede tener mas de 64 caracteres*/
#define MAX_LONGITUD_NOMBRE 64

/*Consideraciones a tener en cuenta:
	1.- Para la arquitectura de un sistema se utiliza un
	 	patron COMPOSITE. El objeto general es la clase elemento
	 	de la cual heredean los pulsadores, lamparas, etc...
	2.- Cada elemento es a su vez parte de un patrón OBSERVER. Esto
		permite que haya muchos elementos que conecten su entrada a la
		salida de otros elementos de forma transparente
	3.- En el mismo código SE MEZCLAN los dos patrones. Los elementos
		concretos del patron COMPOSITE son SUSCRIPTORES y OBSERVADORES */

/*Clase padre general de patron COMPOSITE
	Observese que contiene los metodos propios de un OBSERVER*/

#ifndef _elementos_
#define _elementos_
class Elemento {
	public:
		XMLCh*	getNombreElemento	()				;
		void 	anadirSuscriptor   	(Elemento* e)  	;
		void 	eliminarSuscriptor 	(Elemento *e)  	;
		void 	notificar           ()             	;	
        float 	getSalida			();
		//Este metodo puede re-implementarse (y de hecho se hará)
		//en las clases hija
		virtual void construir 	 (DOMNode *nodo)=0;
		virtual	void setEntrada	 (float entrada)	;
	protected:
		void 		inicializar	();
		bool		iguales 	(const XMLCh* cad1, const XMLCh* cad2);
		float		entradaActual,	salidaActual;		
		XMLCh* 		nombreElemento;
		Elemento* 	listaSuscriptores[MAX_SUSCRIPTORES];
		int 		totalSuscriptores;
};


/*Los elementos concretos se construyen a partir de un nodo DOM,
  es decir, directamente de un "trozo" en XML*/
  







/*	Esta clase representa la relacion entre un elemento llamado
	primario y otro llamado secundario. La salida del primario
	irá conectada a la entrada del secundario, haciendo que el
	secundario sea un observador del primario (es decir, que el
	secundario estará en la lista de suscripciones del primario) */
class Relacion {
	/*Nombres de los elementos que la componen*/
	XMLCh*		nombrePrimario;
	XMLCh*		nombreSecundario;
	public:
				Relacion			();
		void	construir 			(DOMNode*	nodo);
		XMLCh*	getNombrePrimario	();
		XMLCh*	getNombreSecundario	();	
};
#endif
