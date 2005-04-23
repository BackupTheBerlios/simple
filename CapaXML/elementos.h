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

class reed {
       public:
              reed(DOMNode *nodo);
       private:
               char* nombre ;
               /*Para un cierto magnetismo de entrada hay un voltaje
                *de salida*/
               float entradainicial, salidainicial ;       
               float entradafinal,   salidafinal   ;
};

class pulsador {
      public:
             pulsador (DOMNode *nodo);
      private:
              char* nombreelemento;
              float entradainicial, salidainicial ;
              float entradafinal,   salidafinal   ;
};

class fotosensor {
	public:
		fotosensor (DOMNode *nodo);
	private:
		char* nombreelemento;
		float entradainicial, salidainicial ;
		float entradafina,    salidafinal   ;	
};


class lampara {
	public:
		lampara (DOMNode* nodo);
	private:
		char* nombreelemento;
		float entradainicial, salidainicial ;
		float entradafinal,   salidafinal   ;	
};

class electroiman {
	public:
		electroiman (DOMNode* nodo) ;
	private:
		char *nombreelemento;
		float entradainicial, salidainicial ;
		float entradafinal,   salidafinal ;	
};

class motor {
	public:
		motor (DOMNode* nodo) ;
	private:
		char* nombreelemento;
		float entradagiro1, salidagiro1 ; 
		float entradagiro2, salidagiro2 ;
		float entradaparo,  salidaparo  ;
};
