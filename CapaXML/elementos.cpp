/*Fichero elementos.cpp
	Contiene la implementación de los elementos que forman parte de un
	sistema que se quiere simular
*/

#include "elementos.h"
#include <iostream>


#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif	


/*	Este es el valor inicial que por defecto adoptan
	todas las constantes. Usado para depurar, por lo que a
	si te lo encuentras en la depuración y ningún fichero XML
	lo contiene es porque algún objeto no se ha inicializado a partir
	del XML*/
#define VALOR_INICIAL -7.65


/*En este fichero definimos las clases (objetos funcion) de los
 *distintos elementos*/

using namespace std;

/*Esta funcion la utilizo para no repetir la forma de comparar cadenas
  ya que a menudo he necesitado cambiar los objetos usados para comparar
  asi como la representación interna de las cadenas.
  Simplemente se usa para saber si dos cadenas son iguales*/
bool iguales (const XMLCh* cad1, const XMLCh* cad2)
{
	return XMLString::equals (cad1, cad2);
}


/*	Inicializador generico para todos los elementos
	Cualquier clase hija puede modificarlo*/
	
void elemento::inicializar ()
{
	nombre_elemento=NULL;
	for (int i=0;i<MAX_SUSCRIPTORES;i++)
		lista_suscriptores[i]=NULL;
	total_suscriptores=-1;
	nombre_elemento=NULL;
}
//El constructor solo inicializa*/
reed::reed ()
{
	/*Se llama al inicializador generico*/
	inicializar ();
	
	/*Y se inicializan el resto de miembros*/
	entradainicial	=	entradafinal	=	VALOR_INICIAL;
	salidainicial	=	salidafinal		=	VALOR_INICIAL;
	
	
}

void reed::construir (DOMNode *nodo){
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    printf ("Creando un reed\n");
     
    /*Recorremos las propiedades del reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName();
              valor_propiedad=  hijo->getTextContent() ;
              printf ("Propiedad %s: %s\n", 
                  nombre_propiedad, valor_propiedad);
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }
}


pulsador::pulsador()
{
	inicializar();
	entradainicial	=	entradafinal	=	VALOR_INICIAL;
	salidainicial	=	salidafinal		=	VALOR_INICIAL;
}

void pulsador::construir (DOMNode *nodo) {
    DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    printf ("Creando un pulsador\n");
     
    /*Recorremos las propiedades del reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName() ;
              valor_propiedad=  hijo->getTextContent() ;
              printf ("Propiedad %s: %s\n", 
                  nombre_propiedad, valor_propiedad);
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   
}


fotosensor::fotosensor()
{
	inicializar();
	entradainicial	=	entradafinal	=	VALOR_INICIAL;
	salidainicial	=	salidafinal		=	VALOR_INICIAL;
}

void fotosensor::construir (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    printf ("Creando un fotosensor\n");
     
    /*Recorremos las propiedades del reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=hijo->getNodeName()  ;
              valor_propiedad= hijo->getTextContent();
              printf ("Propiedad %s: %s\n", 
                  nombre_propiedad, valor_propiedad);
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   
}

electroiman::electroiman (){
	inicializar();
	entradainicial	=	entradafinal	=	VALOR_INICIAL;
	salidainicial	=	salidafinal		=	VALOR_INICIAL;
}
void electroiman::construir (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    printf ("Creando un fotosensor\n");
     
    /*Recorremos las propiedades del reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName();
              valor_propiedad= hijo->getTextContent() ;
              printf ("Propiedad %s: %s\n", 
                  nombre_propiedad, valor_propiedad);
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   	
}


lampara::lampara()
{
	inicializar();
	entradainicial	=	entradafinal	=	VALOR_INICIAL;
	salidainicial	=	salidafinal		=	VALOR_INICIAL;
}

void lampara::construir (DOMNode* nodo) {
	    DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    printf ("Creando lampara\n");
     
    /*Recorremos las propiedades del reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=hijo->getNodeName()  ;
              valor_propiedad= hijo->getTextContent();
              printf ("Propiedad %s: %s\n", 
                  nombre_propiedad, valor_propiedad);
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     } 
}


motor::motor()
{
	inicializar();
	entradagiro1	=	entradagiro2	=	VALOR_INICIAL;
	salidagiro1		=	salidagiro2		=	VALOR_INICIAL;
	entradaparo		=	salidaparo		=	VALOR_INICIAL;
}

void motor::construir (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    const XMLCh* elementoXMLabuscar;
    int aux;
    printf ("Creando un motor\n");
     
    /*Recorremos las propiedades del reed...*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName()  ;
              valor_propiedad=  hijo->getTextContent() ;
              elementoXMLabuscar=XMLString::transcode ("nombreelemento");
              /*... y aqui e extraen los valores almacenados en el XML*/
			  if (  iguales (nombre_propiedad, elementoXMLabuscar ) ){
					nombre_elemento= XMLString::replicate (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradagiro1");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradagiro1=XMLString::parseInt (valor_propiedad);
			  }
			  
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   
}

//Falta el destructor de motor
//Tiene que XMLString::release (nombre_elemento);
elemento_compuesto::elemento_compuesto (DOMNode* nodo) {
}
