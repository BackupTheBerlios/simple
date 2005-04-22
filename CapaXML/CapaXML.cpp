#include <cstdlib>
#include <iostream>

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


void crear_reed (DOMNode *nodo)
{
     /*Aqui vamos almacenando los nombres y los valores de las propiedades
       (que se escribieron en XML,del reed que encontremos en el fichero XML*/
     char *nombre_propiedad;
     char *valor_propiedad;
     DOMNode *hijo=nodo->getFirstChild ();
     DOMNode *propiedad;
     printf ("Creando un reed\n");
     
     /*Recorremos las propiedades del reed*/
     while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=XMLString::transcode ( hijo->getNodeName()  );
              valor_propiedad= XMLString::transcode ( hijo->getTextContent() );
              printf ("Propiedad %s: %s\n", 
                  nombre_propiedad, valor_propiedad);
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }
}
void crear_elementos (DOMDocument *documento)
{
  int codigo_igualdad;
  
  /*El TreeWalker me permite recorrer el arbol pero
   ¡¡ATENCION!!: Uso un filtro que solo me muestra elementos y 
   NUNCA me muestra atributos*/
  DOMTreeWalker *arbol=documento->createTreeWalker ( (DOMNode*) documento, 
                DOMNodeFilter::SHOW_ELEMENT, NULL, true );
                
  //El primer hijo del documento es el elemento raiz
  DOMNode *nodoactual=arbol->firstChild();
  
  //Y dentro del documento raiz es donde estan los elementos
  //hijo que nos interesan
  nodoactual=nodoactual->getFirstChild();

  //Recorremos todos los elementos hijo creando elementos...
  while (nodoactual)
  {
        if (nodoactual->getNodeType() == DOMNode::ELEMENT_NODE)
        {
           char* cad_codificada=XMLString::transcode (nodoactual->getNodeName());
           cout << "Construyendo un " << cad_codificada << endl;
           codigo_igualdad=strcmp(cad_codificada, "reed");
           if (codigo_igualdad==0) 
           {
              /*Procesamos el nodo actual en busca de un reed*/
              crear_reed (nodoactual);
           }
           XMLString::release (&cad_codificada);
        }
        nodoactual=nodoactual->getNextSibling ();
  } //Fin del recorrido
    
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
  
  crear_elementos (documento);  
  delete parser;
  delete manejador;

  XMLPlatformUtils::Terminate();
  // Poner aqui el resto de delete's, cuando sean necesarios
  return 0;
}

