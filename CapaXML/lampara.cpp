#include "lampara.h"
#include "constantes.h"
#include <iostream>

using namespace std;

XMLCh* Lampara::getColor()
{
	return color;
}

/*	La lampara tiene que utilizar el metodo "construir" de la clase
	base, pero tenemos que añadir el codigo necesario para encontrar
	el color de esa clase*/
void Lampara::construir (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    XMLCh*		elementoXMLabuscar;
    
    /*Se recogen las propiedades de siempre*/
    ElementoSimple::construir(nodo);
    
    /*Buscamos el color de la lampara dentro del nodo XML*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName();
              valor_propiedad= hijo->getTextContent() ;
              
              elementoXMLabuscar=XMLString::transcode ("color");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					color=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(color);
			  }
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }  /*Fin del while*/
}

DOMElement* Lampara::getNodo()
{
	DOMElement*		nodoColor;
	char*			aux;
	XMLCh*			nombreNodo;
	XMLCh*			valorNodo;
	
	
	/*	Se llama a getNodo en la clase base que hace la mayor parte del
		trabajo, y se terminan de rellenar los campos con esta 
		funcion*/
		ElementoSimple::getNodo("lampara");
	
	/*	Obtenemos una implementación DOM
		Nos basta con que implemente el núcleo (CORE) del
		estándar DOM*/
	DOMImplementation* implementacion=
		DOMImplementationRegistry::getDOMImplementation 
			(XMLString::transcode ("Core"));
	
	
	nombreNodo=XMLString::transcode ("color");
	nodoColor=doc->createElement(nombreNodo);
	nodoColor->setTextContent(this->getColor());
	
	/*	El puntero al documento raiz apunta al minidocumento
		"electroiman" creado antes. Se necesita para empezar
		a insertar elementos dentro del elemento*/
	DOMElement* punteroDocRaiz=doc->getDocumentElement();
	punteroDocRaiz->appendChild (nodoColor);
	punteroDocRaiz->appendChild (nodoEntradaReposo);
	punteroDocRaiz->appendChild (nodoSalidaReposo);
	punteroDocRaiz->appendChild (nodoEntradaActivacion);
	punteroDocRaiz->appendChild (nodoSalidaActivacion);	
	
	/*	Una vez enganchados los elementos, devolvemos el minidocumento*/
	return (DOMElement*) doc;

}
