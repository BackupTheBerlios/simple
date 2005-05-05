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
	private:
		elemento* lista_suscriptores [MAX_SUSCRIPTORES];
		int total_suscriptores;
};


/*Los elementos concretos se construyen a partir de un nodo DOM,
  es decir, directamente de un "trozo" en XML*/
  
class reed : public elemento {
       public:
              reed(DOMNode *nodo);
       private:
               char* nombre ;
               /*Para un cierto magnetismo de entrada hay un voltaje
                *de salida*/
               float entradainicial, salidainicial ;       
               float entradafinal,   salidafinal   ;
};

class pulsador: public elemento {
      public:
             pulsador (DOMNode *nodo);
      private:
              XMLCh* nombreelemento;
              float entradainicial, salidainicial ;
              float entradafinal,   salidafinal   ;
};

class fotosensor: public elemento {
	public:
		fotosensor (DOMNode *nodo);
	private:
		XMLCh* nombreelemento;
		float entradainicial, salidainicial ;
		float entradafina,    salidafinal   ;	
};


class lampara: public elemento {
	public:
		lampara (DOMNode* nodo);
	private:
		XMLCh* nombreelemento;
		float entradainicial, salidainicial ;
		float entradafinal,   salidafinal   ;	
};

class electroiman: public elemento {
	public:
		electroiman (DOMNode* nodo) ;
	private:
		XMLCh *nombreelemento;
		float entradainicial, salidainicial ;
		float entradafinal,   salidafinal ;	
};

class motor: public elemento {
	public:
		motor (DOMNode* nodo) ;
	private:
		XMLCh* nombreelemento;
		float entradagiro1, salidagiro1 ; 
		float entradagiro2, salidagiro2 ;
		float entradaparo,  salidaparo  ;
};

class elemento_compuesto: public elemento {
	public:
		elemento_compuesto (DOMNode* nodo) ;
	private:
		XMLCh *nombreelemento;	
};

#endif
