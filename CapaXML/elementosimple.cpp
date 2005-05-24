/*	Implementacion de ElementoSimple. Aqui se define comportamiento común
	a muchos elementos de naturaleza muy simple: Pulsadores, fotosensores
	lámparas, pulsadores, reeds y zumbadores*/
	
	
	
#include "elementosimple.h"
#include "constantes.h"

	
/*	El constructor inicializa los valores de las entradas y salidas a
	un valor por defecto. Además, llama a inicializar(), en la clase
	base "Elemento", que inicializa los vectores de observadores*/

ElementoSimple::ElementoSimple()
{
	inicializar();
	entradaReposo	=	salidaReposo	=	VALOR_INICIAL;
	salidaActivacion=	salidaActivacion=	VALOR_INICIAL;	
}	

/*	Se recibe un nodo DOM que contiene (en formato XML) las propiedades
	del elemento en cuestión. A grandes rasgos, lo que hacemos es recorrer
	todas las propiedades, buscando las que nos interesan, y extraemos
	los valores almacenados en los elementos XML*/
void ElementoSimple::construir (DOMNode* nodo) {
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


/*Metodos getter de las propiedades básicas*/
float ElementoSimple::getEntradaReposo()
{
	return entradaReposo;
}
float ElementoSimple::getEntradaActivacion()
{
	return entradaActivacion;
}
float ElementoSimple::getSalidaReposo()
{
	return salidaReposo;
}
float ElementoSimple::getSalidaActivacion()
{
	return salidaActivacion;
}

void ElementoSimple::setEntrada(float entrada)
{
	Elemento::setEntrada(entrada);
	if (entradaActual==entradaReposo)
	{
		salidaActual=salidaReposo;
		notificar();
	}
	if (entradaActual==entradaActivacion)
	{
		salidaActual=salidaActivacion;
		notificar();
	}
}


DOMElement* ElementoSimple::getNodo(char *nombreElemento)
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
	
	/*	Se va a implementar un minidocumento electroiman. Los documentos
		en general se pueden "incrustar" dentro de otros documentos.
		No usa espacios de nombres (0), se llamara "electroiman"
		y no le ponemos ningun tipo al documento (0)*/
	doc= implementacion->createDocument 
		(0, XMLString::transcode (nombreElemento), 0);
	
	
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
