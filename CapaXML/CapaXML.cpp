#include <cstdlib>
#include <iostream>

//Evitar instanciación de plantillas
#define XERCES_TMPLSINC

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

using namespace std;

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif	

//Mejorar esta funcion
static int recorre(DOMNode *n, bool imprimir, int nivel)
{
    DOMNode *hijo;
    int count = 0;
    //cout << endl << endl << "Estamos en el nivel " << nivel << endl;
    if ( (nivel<=2) && (n!=NULL) ) {
        if (n->getNodeType() == DOMNode::ELEMENT_NODE)
		{
            if(imprimir) {
                char *nombre = XMLString::transcode(n->getNodeName());
                XERCES_STD_QUALIFIER cout <<"----------------------------------------------------------"<<XERCES_STD_QUALIFIER endl;
                XERCES_STD_QUALIFIER cout <<"Elemento (objeto a crear): "
                                     << nombre << XERCES_STD_QUALIFIER endl;
                
                XMLString::release(&nombre);
			
                if(n->hasAttributes()) {
                    // Sacar los atributos de un nodo
                    DOMNamedNodeMap *pAttributes = n->getAttributes();
                    int tam = pAttributes->getLength();
                    XERCES_STD_QUALIFIER cout <<"\tAtributos" << XERCES_STD_QUALIFIER endl;
                    XERCES_STD_QUALIFIER cout <<"\t----------" << XERCES_STD_QUALIFIER endl;
                    for(int i=0;i<tam;++i) {
                        DOMAttr *pAttributeNode = (DOMAttr*) pAttributes->item(i);
                        // Sacar el nombre
                        char *nombre = XMLString::transcode(pAttributeNode->getName());
                        
                        XERCES_STD_QUALIFIER cout << "\t" << nombre << "=";
                        XMLString::release(&nombre);
                        
                        // Sacar el tipo del atributo
                        nombre = XMLString::transcode(pAttributeNode->getValue());
                        XERCES_STD_QUALIFIER cout << nombre << XERCES_STD_QUALIFIER endl;
                        XMLString::release(&nombre);
                    }
                }
            }
			++count;
		}
        for (hijo = n->getFirstChild(); hijo != 0; hijo=hijo->getNextSibling())
            count += recorre (hijo, imprimir, nivel+1);
    }
    return count;
}



int main(int argc, char* argv[])
{

  // 

  XMLPlatformUtils::Initialize();


  const XMLCh* nombrefichero;
  
  //Creamos el parser
  XercesDOMParser *parser= new XercesDOMParser();
  //Queremos que sea un parser validador
  parser->setValidationScheme (XercesDOMParser::Val_Always);
  //Queremos ceñirnos al espacio de nombre
  parser->setDoNamespaces (true);
  //Activamos el soporta para XMLSchemas
  parser->setDoSchema (true);
  //Cargamos el esquema ¡es importante poner el espacio de
  //nombres y el fichero. En este caso el espacio viene
  //definido por http... y el fichero es sistema.xsd
  parser->setExternalSchemaLocation("http://www.w3schools.com sistema.xsd");
  
  ErrorHandler* manejador= (ErrorHandler *) new HandlerBase();
  parser->setErrorHandler (manejador);
  
  char *fichero="proyecto.xml";
  
  try{
      parser->parse(fichero);
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
  
  //El TreeWalker me permite recorrer el arbol
  DOMTreeWalker *arbol=documento->createTreeWalker ( (DOMNode*) documento, 
                DOMNodeFilter::SHOW_ALL, NULL, true );
  DOMNode *nodoactual=arbol->firstChild();
  
  recorre (nodoactual,true,1);
  nodoactual=nodoactual->getFirstChild();
  //Recorrido del arbol
  cout << endl << "Fase 3: Construccion de los objetos" << endl ;
  while (nodoactual)
  {
        if (nodoactual->getNodeType() == DOMNode::ELEMENT_NODE)
        {
           char* cad_codificada=XMLString::transcode (nodoactual->getNodeName());
           cout << "Construyendo un " << cad_codificada << endl;
           XMLString::release (&cad_codificada);
        }
        nodoactual=nodoactual->getNextSibling ();
  }

  delete parser;
  delete manejador;

  XMLPlatformUtils::Terminate();
  // Poner aqui el resto de delete's, cuando sean necesarios
  return 0;
}

