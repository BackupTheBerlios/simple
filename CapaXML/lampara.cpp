#include "lampara.h"
#include "constantes.h"
#include <iostream>

using namespace std;
Lampara::Lampara()
{
	inicializar();
	entradaReposo	=	entradaActivacion	=	VALOR_INICIAL;
	salidaReposo	=	salidaActivacion	=	VALOR_INICIAL;
}

void Lampara::construir (DOMNode* nodo) {
    DOMNode*		propiedad ;
    const XMLCh*	nombre_propiedad ;
    const XMLCh*	valor_propiedad ;
    const XMLCh*	elementoXMLabuscar;
    /*Recorremos las propiedades del Reed*/
    
    DOMNode* hijo=nodo->getFirstChild () ;
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=hijo->getNodeName()  ;
              valor_propiedad= hijo->getTextContent();
			  elementoXMLabuscar=XMLString::transcode ("nombreelemento");
			  /*... y aqui se extraen los valores almacenados en el XML*/
			  if (  iguales (nombre_propiedad, elementoXMLabuscar ) ){
					nombreElemento= XMLString::replicate (valor_propiedad);
					XMLString::removeWS(nombreElemento);
					char *nombre=XMLString::transcode (nombreElemento);
					cout << "La lampara se llama:" << nombre <<endl;
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("color");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					color=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(color);
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

/*Metodos getter de Lampara*/
float Lampara::getEntradaReposo()
{
	return entradaReposo;
}
float Lampara::getEntradaActivacion()
{
	return entradaActivacion;
}
float Lampara::getSalidaReposo()
{
	return salidaReposo;
}
float Lampara::getSalidaActivacion()
{
	return salidaActivacion;
}
XMLCh* Lampara::getColor()
{
	return color;
}

void Lampara::setEntrada(float entrada)
{
	Elemento::setEntrada(entrada);
	if (entradaActual==entradaReposo)
	{
		cout << "Lampara en reposo" << endl;
		salidaActual=salidaReposo;
		notificar();
	}
	if (entradaActual==entradaActivacion)
	{
		salidaActual=salidaActivacion;
		cout << "Lampara encendida! " << salidaActual<<endl;
		notificar();
	}
}

