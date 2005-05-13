#include "pulsador.h"
#include <iostream>
using namespace std;
Pulsador::Pulsador()
{
	inicializar();
	entradaReposo		=	entradaActivacion	=	VALOR_INICIAL;
	salidaReposo		=	salidaActivacion	=	VALOR_INICIAL;
}

float Pulsador::getEntradaReposo()
{
	return entradaReposo;
}

float Pulsador::getSalidaReposo()
{
	return salidaReposo;
}

float Pulsador::getEntradaActivacion()
{
	return entradaActivacion;
}

float Pulsador::getSalidaActivacion()
{
	return salidaActivacion;
}

void Pulsador::construir (DOMNode *nodo) {
    DOMNode *propiedad 				;
    const XMLCh *nombre_propiedad 	;
    const XMLCh *valor_propiedad 	;
    XMLCh*		elementoXMLabuscar	;
    
    DOMNode *hijo=nodo->getFirstChild () ;
    /*Recorremos las propiedades del Reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName() ;
              valor_propiedad=  hijo->getTextContent() ;
              
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
void Pulsador::setEntrada(float entrada)
{
	Elemento::setEntrada(entrada);
	if (entradaActual==entradaReposo)
	{
		std::cout << "Pulsador en reposo" << endl;
		salidaActual=salidaReposo;
		notificar();
	}
	if (entradaActual==entradaActivacion)
	{
		salidaActual=salidaActivacion;
		std::cout << "Pulsador activando y emitiendo " << salidaActual<<endl;
		notificar();
	}
}
