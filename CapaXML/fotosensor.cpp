#include "fotosensor.h"

/*Definicion de la implementacion de FotoSensor*/
FotoSensor::FotoSensor()
{
	inicializar();
	entradaReposo		=	entradaActivacion	=	VALOR_INICIAL;
	salidaReposo		=	salidaActivacion	=	VALOR_INICIAL;
}

void FotoSensor::construir (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    XMLCh* elementoXMLabuscar;
    /*Recorremos las propiedades del Reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=hijo->getNodeName()  ;
              valor_propiedad= hijo->getTextContent();
              elementoXMLabuscar=XMLString::transcode ("nombreelemento");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					nombreElemento=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(nombreElemento);
			  }
              
              elementoXMLabuscar=XMLString::transcode ("entradaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaActivacion=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaActivacion=XMLString::parseInt (valor_propiedad);
			  }
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   
}

float FotoSensor::getEntradaReposo()
{
	return entradaReposo;
}

float FotoSensor::getSalidaReposo()
{
	return salidaReposo;
}

float FotoSensor::getEntradaActivacion()
{
	return entradaActivacion;
}

float FotoSensor::getSalidaActivacion()
{
	return salidaActivacion;
}

