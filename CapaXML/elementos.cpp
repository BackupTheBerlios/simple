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
	
void Elemento::inicializar ()
{
	nombreElemento=NULL;
	for (int i=0;i<MAX_SUSCRIPTORES;i++)
		listaSuscriptores[i]=NULL;
	totalSuscriptores=-1;
	nombreElemento=NULL;
}

XMLCh* Elemento::getNombreElemento ()
{
	return nombreElemento;
}
//El constructor solo inicializa*/
Reed::Reed ()
{
	/*Se llama al inicializador generico*/
	inicializar ();
	
	/*Y se inicializan el resto de miembros*/
	entradaInicial	=	entradaFinal	=	VALOR_INICIAL;
	salidaInicial	=	salidaFinal		=	VALOR_INICIAL;
	
	
}

void Reed::construir (DOMNode *nodo){
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    printf ("Creando un Reed\n");
     
    /*Recorremos las propiedades del Reed*/
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


Pulsador::Pulsador()
{
	inicializar();
	entradaInicial	=	entradaFinal	=	VALOR_INICIAL;
	salidaInicial	=	salidaFinal		=	VALOR_INICIAL;
}

void Pulsador::construir (DOMNode *nodo) {
    DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    printf ("Creando un Pulsador\n");
     
    /*Recorremos las propiedades del Reed*/
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


FotoSensor::FotoSensor()
{
	inicializar();
	entradaInicial	=	entradaFinal	=	VALOR_INICIAL;
	salidaInicial	=	salidaFinal		=	VALOR_INICIAL;
}

void FotoSensor::construir (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    printf ("Creando un FotoSensor\n");
     
    /*Recorremos las propiedades del Reed*/
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

Electroiman::Electroiman (){
	inicializar();
	entradaInicial	=	entradaFinal	=	VALOR_INICIAL;
	salidaInicial	=	salidaFinal		=	VALOR_INICIAL;
}
void Electroiman::construir (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    printf ("Creando un FotoSensor\n");
     
    /*Recorremos las propiedades del Reed*/
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


Lampara::Lampara()
{
	inicializar();
	entradaInicial	=	entradaFinal	=	VALOR_INICIAL;
	salidaInicial	=	salidaFinal		=	VALOR_INICIAL;
}

void Lampara::construir (DOMNode* nodo) {
	    DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    printf ("Creando Lampara\n");
     
    /*Recorremos las propiedades del Reed*/
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


Motor::Motor()
{
	inicializar();
	entradaGiro1	=	entradaGiro2	=	entradaReposo	=	VALOR_INICIAL;
	salidaGiro1		=	salidaGiro2		=	salidaReposo	=	NULL;
}

/*	El destructor de la clase Motor debe liberar
	las cadenas que fueron asignadas directamente por Xerces*/
Motor::~Motor()
{
	XMLString::release	(&salidaGiro1);
	XMLString::release	(&salidaGiro2);
	XMLString::release	(&salidaReposo);
}
void Motor::construir (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    const XMLCh* elementoXMLabuscar;
    int aux;
    printf ("Creando un Motor\n");
     
    /*Recorremos las propiedades del Reed...*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName()  ;
              valor_propiedad=  hijo->getTextContent() ;
              elementoXMLabuscar=XMLString::transcode ("nombreelemento");
              /*... y aqui e extraen los valores almacenados en el XML*/
			  if (  iguales (nombre_propiedad, elementoXMLabuscar ) ){
					nombreElemento= XMLString::replicate (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradagiro1");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaGiro1=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidagiro1");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaGiro1=XMLString::replicate (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradagiro2");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaGiro2=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidagiro2");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaGiro2=XMLString::replicate (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaReposo=XMLString::replicate (valor_propiedad);
			  }
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   
}

float Motor::getEntradaGiro1 () const 
{
	return entradaGiro1;	
}
float Motor::getEntradaGiro2 () const 
{
	return entradaGiro2;	
}
float Motor::getEntradaReposo () const 
{
	return entradaReposo;	
}

XMLCh* Motor::getSalidaGiro1 () const
{
	return salidaGiro1;
}
XMLCh* Motor::getSalidaGiro2 () const
{
	return salidaGiro2;
}
XMLCh* Motor::getSalidaReposo() const
{
	return salidaReposo;
}
//Falta el destructor de Motor
//Tiene que XMLString::release (nombreElemento);
ElementoCompuesto::ElementoCompuesto (DOMNode* nodo) {
}
