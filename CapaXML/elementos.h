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
               float entrada1, salida1 ;       
               float entrada2, salida2 ;
};
