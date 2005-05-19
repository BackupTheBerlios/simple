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

DOMElement* Lampara::getNodo()
{
	DOMElement* 	nodoElementoActual;
	DOMElement*		nodoColor;
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
		(0, XMLString::transcode ("lampara"), 0);
	
	
	/*	Creamos los nodos hijo y rellenamos su contenido*/
	nombreNodo=XMLString::transcode ("entradareposo");
	nodoEntradaReposo=doc->createElement(nombreNodo);
	valorNodo= convertir (entradaReposo);
	nodoEntradaReposo->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("salidareposo");
	nodoSalidaReposo=doc->createElement(nombreNodo);
	valorNodo= convertir (salidaReposo);
	nodoSalidaReposo->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("entradaactivacion");
	nodoEntradaActivacion=doc->createElement(nombreNodo);
	valorNodo= convertir (entradaActivacion);
	nodoEntradaActivacion->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("salidaactivacion");
	nodoSalidaActivacion=doc->createElement(nombreNodo);
	valorNodo= convertir (salidaActivacion);
	nodoSalidaActivacion->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("color");
	nodoColor=doc->createElement(nombreNodo);
	nodoColor->setTextContent(this->getColor());
	
	/*	El puntero al documento raiz apunta al minidocumento
		"electroiman" creado antes. Se necesita para empezar
		a insertar elementos dentro del elemento*/
	DOMElement* punteroDocRaiz=doc->getDocumentElement();
	punteroDocRaiz->appendChild (nodoEntradaReposo);
	punteroDocRaiz->appendChild (nodoSalidaReposo);
	punteroDocRaiz->appendChild (nodoEntradaActivacion);
	punteroDocRaiz->appendChild (nodoSalidaActivacion);	
	
	/*	Una vez enganchados los elementos, devolvemos el minidocumento*/
	return (DOMElement*) doc;

}
