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

DOMElement* Motor::getNodo()
{
	DOMElement* 	nodoElementoActual;
	DOMElement* 	nodoEntradaGiro1;
	DOMElement* 	nodoSalidaGiro1;
	DOMElement* 	nodoEntradaGiro2;
	DOMElement* 	nodoSalidaGiro2;
	DOMElement*		nodoEntradaReposo;
	DOMElement*		nodoSalidaReposo;
	DOMElement*		nodoNombreElemento;
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
		(0, XMLString::transcode ("pulsador"), 0);
	
	
	/*	Creamos los nodos hijo y rellenamos su contenido*/
	nombreNodo=XMLString::transcode ("entradagiro1");
	nodoEntradaGiro1=doc->createElement(nombreNodo);
	valorNodo= convertir (entradaGiro1);
	nodoEntradaGiro1->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("salidagiro1");
	nodoSalidaGiro1=doc->createElement(nombreNodo);
	valorNodo= salidaGiro1;
	nodoSalidaGiro1->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("entradagiro2");
	nodoEntradaGiro2=doc->createElement(nombreNodo);
	valorNodo= convertir (entradaGiro2);
	nodoEntradaGiro2->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("salidagiro2");
	nodoSalidaGiro2=doc->createElement(nombreNodo);
	valorNodo= salidaGiro2;
	nodoSalidaGiro2->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("entradareposo");
	nodoEntradaReposo=doc->createElement(nombreNodo);
	valorNodo= convertir (entradaReposo);
	nodoEntradaReposo->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("salidareposo");
	nodoSalidaReposo=doc->createElement(nombreNodo);
	valorNodo= salidaReposo;
	nodoSalidaReposo->setTextContent(valorNodo);
	
	nombreNodo=XMLString::transcode ("nombreelemento");
	nodoNombreElemento=doc->createElement(nombreNodo);
	valorNodo= getNombreElemento();
	nodoNombreElemento->setTextContent(valorNodo);
	
	/*	El puntero al documento raiz apunta al minidocumento
		"electroiman" creado antes. Se necesita para empezar
		a insertar elementos dentro del elemento*/
	DOMElement* punteroDocRaiz=doc->getDocumentElement();
	punteroDocRaiz->appendChild (nodoEntradaGiro1);
	punteroDocRaiz->appendChild (nodoSalidaGiro1);
	punteroDocRaiz->appendChild (nodoEntradaGiro2);
	punteroDocRaiz->appendChild (nodoSalidaGiro2);	
	punteroDocRaiz->appendChild	(nodoNombreElemento);
	
	/*	Una vez enganchados los elementos, devolvemos el minidocumento*/
	return (DOMElement*) doc;

}
