#include "temporizador.h"


void Temporizador::construir (DOMNode* nodo)
{
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
			  elementoXMLabuscar=XMLString::transcode ("voltajeentradainicial");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					voltajeEntradaInicial=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("voltajesalidainicial");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					voltajeSalidaInicial=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("voltajeactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					voltajeActivacion=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("voltajesalidaentimeout");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					voltajeSalidaEnTimeout=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("tiempo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					tiempo=XMLString::parseInt (valor_propiedad);
			  }
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   	
}
DOMElement*	Temporizador::getNodo()
{
	return Temporizador::getNodo("temporizador");
}
DOMElement* Temporizador::getNodo(char *nombreElemento)
{
	char*			aux;
	XMLCh*			nombreNodo;
	XMLCh*			valorNodo;
	
	
	/*	Obtenemos una implementación DOM
		Nos basta con que implemente el núcleo (CORE) del
		estándar DOM*/
	DOMImplementation* implementacion=
		DOMImplementationRegistry::getDOMImplementation 
			(XMLString::transcode ("Core"));
	
	doc= implementacion->createDocument 
		(0, XMLString::transcode (nombreElemento), 0);
	
	
	/*	Creamos los nodos hijo y rellenamos su contenido*/
	nombreNodo=XMLString::transcode ("voltajeentradainicial");
	nodoVoltajeEntradaInicial=doc->createElement(nombreNodo);
	valorNodo= convertir (voltajeEntradaInicial);
	nodoVoltajeEntradaInicial->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("voltajesalidainicial");
	nodoVoltajeSalidaInicial=doc->createElement(nombreNodo);
	valorNodo= convertir (voltajeSalidaInicial);
	nodoVoltajeSalidaInicial->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("voltajeactivacion");
	nodoVoltajeActivacion=doc->createElement(nombreNodo);
	valorNodo= convertir (voltajeActivacion);
	nodoVoltajeActivacion->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("voltajesalidaentimeout");
	nodoVoltajeSalidaEnTimeout=doc->createElement(nombreNodo);
	valorNodo= convertir (voltajeSalidaEnTimeout);
	nodoVoltajeSalidaEnTimeout->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("tiempo");
	nodoTiempo=doc->createElement(nombreNodo);
	valorNodo= convertir (tiempo);
	nodoTiempo->setTextContent(valorNodo);
	
	/*	El puntero al documento raiz apunta al minidocumento
		creado antes. Se necesita para empezar
		a insertar elementos dentro del elemento*/
	DOMElement* punteroDocRaiz=doc->getDocumentElement();
	punteroDocRaiz->appendChild (nodoVoltajeEntradaInicial);
	punteroDocRaiz->appendChild (nodoVoltajeSalidaInicial);
	punteroDocRaiz->appendChild (nodoVoltajeActivacion);
	punteroDocRaiz->appendChild (nodoVoltajeSalidaEnTimeout);	
	punteroDocRaiz->appendChild (nodoTiempo);	
	
	/*	Una vez enganchados los elementos, devolvemos el minidocumento*/
	return (DOMElement*) doc;

}
