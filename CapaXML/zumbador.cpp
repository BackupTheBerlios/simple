#include "zumbador.h"
//El constructor solo inicializa los miembros de la clase*/
Zumbador::Zumbador()
{
	/*Se llama al inicializador generico*/
	inicializar ();
	
	/*Y se inicializan el resto de miembros*/
	entradaReposo		=	salidaReposo		=	VALOR_INICIAL;
	entradaActivacion	=	salidaActivacion	=	VALOR_INICIAL;
	
	
}
void Zumbador::construir (DOMNode *nodo){
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    XMLCh* elementoXMLabuscar;
    /*Recorremos las propiedades del Zumbador*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName();
              valor_propiedad=  hijo->getTextContent() ;
              
              /*.. y a extraer propiedades*/
              elementoXMLabuscar=XMLString::transcode ("nombreelemento");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					nombreElemento=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(nombreElemento);
			  }
              
              elementoXMLabuscar=XMLString::transcode ("entradareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaActivacion=XMLString::parseInt (valor_propiedad);
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

/*Metodos getter del Zumbador*/
float Zumbador::getEntradaReposo()
{
	return entradaReposo;
}
float Zumbador::getSalidaReposo()
{
	return salidaReposo;
}
float Zumbador::getEntradaActivacion()
{
	return entradaActivacion;
}
float Zumbador::getSalidaActivacion()
{
	return salidaActivacion;
}

DOMElement* Zumbador::getNodo()
{
	DOMElement* 	nodoElementoActual;
	DOMElement* 	nodoEntradaReposo;
	DOMElement* 	nodoSalidaReposo;
	DOMElement* 	nodoEntradaActivacion;
	DOMElement* 	nodoSalidaActivacion;
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
	
	nombreNodo=XMLString::transcode ("nombreelemento");
	nodoNombreElemento=doc->createElement(nombreNodo);
	valorNodo= getNombreElemento();
	nodoSalidaActivacion->setTextContent(valorNodo);
	
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
