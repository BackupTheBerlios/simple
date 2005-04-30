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

  // 

  try {
		XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& tocatch) {
		cout << "Error!" <<endl ;
  }


  {
	const XMLCh* nombrefichero;
  
  //Creamos el parser
  XercesDOMParser *parser= new XercesDOMParser();
  //Queremos que sea un parser validador
  parser->setValidationScheme (XercesDOMParser::Val_Always);
  //Queremos ceñirnos al espacio de nombre
  parser->setDoNamespaces (true);
  //Activamos el soporta para XMLSchemas 
  
  //¡DA ERROR DE MOMENTO!
  //parser->setDoSchema (true);
  //Cargamos el esquema ¡es importante poner el espacio de
  //nombres y el fichero. En este caso el espacio viene
  //definido por http... y el fichero es sistema.xsd
  parser->setExternalSchemaLocation("http://www.w3schools.com sistema.xsd");
  
  ErrorHandler* manejador= (ErrorHandler *) new HandlerBase();
  parser->setErrorHandler (manejador);
  
  XMLCh *fichero=XMLString::transcode ("proyecto.xml");
  cout << "Comienza el baile";
  try{
		cout<< "Parseando" ;
	  parser->parse (fichero);
  }
  catch (XMLException &excepcion)
  {
        char *mensaje=XMLString::transcode (excepcion.getMessage());
        cout << "Excepcion: " << mensaje;
        XMLString::release(&mensaje);
        exit (-1);
  }
  catch (DOMException &excepcion)
  {
        char *mensaje=XMLString::transcode (excepcion.msg);
        cout << "Excepcion: " << mensaje;
        XMLString::release(&mensaje);
        exit (-1);
  }
  catch (...)
  {
        cout << "Excepcion inesperada" << endl;
        cout << "Error!";
        exit (-1);
  }
  cout << "Fase 1: Analisis" << endl ;
  cout << "El fichero es correcto segun el XML Schema proporcionado" << endl;
  
  cout << endl << endl ;
  
  cout << "Fase 2: Lectura de los objetos descritos en el fichero XML" << endl ;
  //Dame el documento parseado
  DOMDocument *documento=parser->getDocument();
  
  /*Temporalmente comentado para factorizar
  crear_elementos (documento);  */
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

