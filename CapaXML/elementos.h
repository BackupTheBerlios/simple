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
class elemento {
	public:
		void cambiar_entrada     (float entrada);
		void anadir_suscriptor   (elemento* e)  ;
		void eliminar_suscriptor (elemento *e)  ;
		void notificar           ()             ;	
		//Este metodo puede re-implementarse (y de hecho se hará)
		//en las clases hija
		virtual void construir 	 (DOMNode *nodo)=0;
	protected:
		void inicializar();
		XMLCh* 		nombre_elemento;
		elemento* 	lista_suscriptores [MAX_SUSCRIPTORES];
		int 		total_suscriptores;
};


/*Los elementos concretos se construyen a partir de un nodo DOM,
  es decir, directamente de un "trozo" en XML*/
  
class reed : public elemento {
       public:
              reed();
              void construir (DOMNode* nodo);
       private:
               /*Para un cierto magnetismo de entrada hay un voltaje
                *de salida*/
               float entradainicial, salidainicial ;       
               float entradafinal,   salidafinal   ;
};

class pulsador: public elemento {
      public:
             pulsador ();
             void construir (DOMNode* nodo);
      private:
              float entradainicial, salidainicial ;
              float entradafinal,   salidafinal   ;
};

class fotosensor: public elemento {
	public:
		fotosensor ();
		void construir (DOMNode* nodo);
	private:
		float entradainicial, salidainicial ;
		float entradafinal,    salidafinal   ;	
};


class lampara: public elemento {
	public:
		lampara ();
		void construir (DOMNode* nodo);
	private:
		float entradainicial, salidainicial ;
		float entradafinal,   salidafinal   ;	
};

class electroiman: public elemento {
	public:
		electroiman () ;
		void construir (DOMNode* nodo);
	private:
		float entradainicial, salidainicial ;
		float entradafinal,   salidafinal ;	
};

class motor: public elemento {
	public:
		motor () ;
		void construir (DOMNode* nodo);
	private:
		float entradagiro1, salidagiro1 ; 
		float entradagiro2, salidagiro2 ;
		float entradaparo,  salidaparo  ;
};

class elemento_compuesto: public elemento {
	public:
		elemento_compuesto (DOMNode* nodo) ;
};

#endif
