#include "contador.h"

DOMElement* Contador::getNodo()
{
	return ElementoSimple::getNodo("contador");
}



/*		La mayor parte del proceso la puede realizar la clase padre
		pero además hay que buscan un elemento XML llamado "numerodepulsos"
		que contiene el valor que tiene que alcanzar el contador antes
		de sacar por la salida el valor "salidaactivacion"*/
void Contador::construir (DOMNode* nodo)
{
	
	/*	En general, en el contador solo analizamos el nodo en busca
		del "numerodepulsos"*/
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    XMLCh*		elementoXMLabuscar;
    /*Recorremos las propiedades */
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName();
              valor_propiedad= hijo->getTextContent() ;
              
              elementoXMLabuscar=XMLString::transcode ("numerodepulsos");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					numeroDePulsos=XMLString::parseInt (valor_propiedad);
			  }
           }
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }      
	 /*	En la clase padre se busca el resto de valores*/
	 ElementoSimple::construir (nodo);
}

float Contador::getNumeroDePulsos()
{
	return numeroDePulsos;
}

/*	El contador actua de forma ligeramente distinta a otros elementos por
	lo que hay que redefinir este metodo*/
void Contador::setEntrada(float entrada)
{
	/*	Si se produce un nuevo cambio de entrada de forma que pasemos de
		"entradareposo" a entradaactivacion tenemos un nuevo pulso. Si hemos
		alcanzado la cuenta de pulsos, notificamos el evento*/
	if ( (entradaActual==entradaReposo) && (entrada==entradaActivacion) )
	{
		contadorDePulsos++;
		if (contadorDePulsos==numeroDePulsos)
		{
			contadorDePulsos=0;
			salidaActual=salidaActivacion;
			notificar();
		}
	}
}

/*	Resetea el contador*/
void	Contador::reset()
{
	entradaActual	=entradaReposo;
	salidaActual	=salidaReposo;
	contadorDePulsos=0;
	notificar();
}
