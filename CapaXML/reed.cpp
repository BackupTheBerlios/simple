#include "reed.h"

//El constructor solo inicializa*/
Reed::Reed ()
{
	/*Se llama al inicializador generico*/
	inicializar ();
	
	/*Y se inicializan el resto de miembros*/
	entradaReposo		=	salidaReposo		=	VALOR_INICIAL;
	entradaActivacion	=	salidaActivacion	=	VALOR_INICIAL;
	
	
}

void Reed::construir (DOMNode *nodo){
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

/*Metodos getter del Reed*/
float Reed::getEntradaReposo()
{
	return entradaReposo;
}
float Reed::getSalidaReposo()
{
	return salidaReposo;
}
float Reed::getEntradaActivacion()
{
	return entradaActivacion;
}
float Reed::getSalidaActivacion()
{
	return salidaActivacion;
}
