#include "motor.h"
#include "constantes.h"

/*	Definicion del motor*/
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
					XMLString::removeWS(nombreElemento);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradagiro1");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaGiro1=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidagiro1");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaGiro1=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(salidaGiro1);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradagiro2");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaGiro2=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidagiro2");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaGiro2=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(salidaGiro2);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaReposo=XMLString::replicate (valor_propiedad);
					XMLString::removeWS (salidaReposo);
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
