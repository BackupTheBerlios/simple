
#include "electroiman.h"
#include "constantes.h"
#include <stdio.h>

Electroiman::Electroiman (){
	inicializar();
	entradaReposo	=	salidaReposo	=	VALOR_INICIAL;
	salidaActivacion=	salidaActivacion=	VALOR_INICIAL;
}
void Electroiman::construir (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    XMLCh*		elementoXMLabuscar;
    /*Recorremos las propiedades del Reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName();
              valor_propiedad= hijo->getTextContent() ;
              
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

/*Metodos getter de Electroiman*/
float Electroiman::getEntradaReposo()
{
	return entradaReposo;
}
float Electroiman::getEntradaActivacion()
{
	return entradaActivacion;
}
float Electroiman::getSalidaReposo()
{
	return salidaReposo;
}
float Electroiman::getSalidaActivacion()
{
	return salidaActivacion;
}

DOMElement* Electroiman::getNodo()
{
	DOMElement* 	nodoElementoActual;
	DOMElement* 	nodoEntradaReposo;
	DOMElement* 	nodoSalidaReposo;
	DOMElement* 	nodoEntradaActivacion;
	DOMElement* 	nodoSalidaActivacion;
	char*			aux;
	XMLCh*			nombreNodo;
	XMLCh*			valorNodo;
	
	
	/*	Obtenemos una implementación DOM
		Nos basta con que implemente el núcleo (CORE) del
		estándar DOM*/
	DOMImplementation* implementacion=
		DOMImplementationRegistry::getDOMImplementation 
			(XMLString::transcode ("Core"));
	
	/*	Se va a implementar un minidocumento electroiman. Los documentos
		en general se pueden "incrustar" dentro de otros documentos.
		No usa espacios de nombres (0), se llamara "electroiman"
		y no le ponemos ningun tipo al documento (0)*/
	DOMDocument* doc= implementacion->createDocument 
		(0, XMLString::transcode ("electroiman"), 0);
	
	/*	El puntero al documento raiz apunta al minidocumento
		"electroiman" creado antes. Se necesita para empezar
		a insertar elementos dentro del elemento*/
	DOMElement* punteroDocRaiz=doc->getDocumentElement();
	
	/*	Creamos los nodos hijo y rellenamos su contenido*/
	nombreNodo=XMLString::transcode ("entradareposo");
	nodoEntradaReposo=doc->createElement(nombreNodo);
	valorNodo= convertir (entradaReposo);
	nodoEntradaReposo->setTextContent(valorNodo);
	
	

}
