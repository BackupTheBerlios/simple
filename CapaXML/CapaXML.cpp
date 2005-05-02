#include <iostream>
#include "elementos.h"

//Evitar instanciación de plantillas
#define XERCES_TMPLSINC

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>


//Otra cosa mas

using namespace std;

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif	



void crear_elementos (DOMNode *nodoactual)
{
  int codigo_igualdad;
  
 nodoactual= nodoactual->getFirstChild();
 
  //Recorremos todos los elementos hijo creando elementos...
 
        if (nodoactual->getNodeType() == DOMNode::ELEMENT_NODE)
        {
           char* cad_codificada=XMLString::transcode (nodoactual->getNodeName());
           cout << "Construyendo un " << cad_codificada << endl;
           codigo_igualdad=strcmp(cad_codificada, "reed");
           if (codigo_igualdad==0) 
           {
              /*Procesamos el nodo actual en busca de un reed*/
              reed *r=new reed (nodoactual) ;
           }
           
           codigo_igualdad=strcmp(cad_codificada, "pulsador");
           if (codigo_igualdad==0) 
           {
              /*Procesamos el nodo actual en busca de un reed*/
              pulsador *r=new pulsador (nodoactual) ;
           }
           
           codigo_igualdad=strcmp(cad_codificada, "lampara");
           if (codigo_igualdad==0) 
           {
              /*Procesamos el nodo actual en busca de un reed*/
              lampara *r=new lampara (nodoactual) ;
           }
           
           codigo_igualdad=strcmp(cad_codificada, "fotosensor");
           if (codigo_igualdad==0) 
           {
              /*Procesamos el nodo actual en busca de un reed*/
              fotosensor *r=new fotosensor (nodoactual) ;
           }
           
           codigo_igualdad=strcmp(cad_codificada, "motor");
           if (codigo_igualdad==0) 
           {
              /*Procesamos el nodo actual en busca de un reed*/
              motor *r=new motor (nodoactual) ;
           }
           
           
           XMLString::release (&cad_codificada) ;
	}
} //Fin del recorrido
    

int main(int argc, char* argv[])
{

  cout << "Fase 2: Lectura de los objetos descritos en el fichero XML" << endl ;
  //Dame el documento parseado
  DOMDocument *documento=parser->getDocument();
  
  crear_elementos (documento);  
  char *nombreelemento="motor";
  XMLCh *elemento=XMLString::transcode (nombreelemento) ;
  DOMNodeList* lista= documento->getElementsByTagName(elemento);
  XMLString::release (&elemento);
  XMLSize_t indice;
  
  /*¡¡Cuidado, la longitud de una NodeList es de 0 a length-1!!!*/
  for (indice=0 ; indice <lista->getLength() ; indice++)
	{
		crear_elementos (lista->item (indice) );
	}
  delete parser;
  delete manejador;
}
  XMLPlatformUtils::Terminate();
  // Poner aqui el resto de delete's, cuando sean necesarios
  return 0;
}

