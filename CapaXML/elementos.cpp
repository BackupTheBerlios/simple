#include "elementos.h"
#include <iostream>
#include <cstring>

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif	

/*En este fichero definimos las clases (objetos funcion) de los
 *distintos elementos*/

using namespace std;

reed::reed(DOMNode *nodo){
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    char *nombre_propiedad ;
    char *valor_propiedad ;
    printf ("Creando un reed\n");
     
    /*Recorremos las propiedades del reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=XMLString::transcode ( hijo->getNodeName()  );
              valor_propiedad= XMLString::transcode ( hijo->getTextContent() );
              printf ("Propiedad %s: %s\n", 
                  nombre_propiedad, valor_propiedad);
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }
}

pulsador::pulsador (DOMNode *nodo) {
    DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    char *nombre_propiedad ;
    char *valor_propiedad ;
    printf ("Creando un pulsador\n");
     
    /*Recorremos las propiedades del reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=XMLString::transcode ( hijo->getNodeName()  );
              valor_propiedad= XMLString::transcode ( hijo->getTextContent() );
              printf ("Propiedad %s: %s\n", 
                  nombre_propiedad, valor_propiedad);
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   
}

fotosensor::fotosensor (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    char *nombre_propiedad ;
    char *valor_propiedad ;
    printf ("Creando un fotosensor\n");
     
    /*Recorremos las propiedades del reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=XMLString::transcode ( hijo->getNodeName()  );
              valor_propiedad= XMLString::transcode ( hijo->getTextContent() );
              printf ("Propiedad %s: %s\n", 
                  nombre_propiedad, valor_propiedad);
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   
}

electroiman::electroiman (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    char *nombre_propiedad ;
    char *valor_propiedad ;
    printf ("Creando un fotosensor\n");
     
    /*Recorremos las propiedades del reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=XMLString::transcode ( hijo->getNodeName()  );
              valor_propiedad= XMLString::transcode ( hijo->getTextContent() );
              printf ("Propiedad %s: %s\n", 
                  nombre_propiedad, valor_propiedad);
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   	
}

lampara::lampara (DOMNode* nodo) {
	    DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    char *nombre_propiedad ;
    char *valor_propiedad ;
    printf ("Creando lampara\n");
     
    /*Recorremos las propiedades del reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=XMLString::transcode ( hijo->getNodeName()  );
              valor_propiedad= XMLString::transcode ( hijo->getTextContent() );
              printf ("Propiedad %s: %s\n", 
                  nombre_propiedad, valor_propiedad);
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     } 
}

motor::motor (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    char *nombre_propiedad ;
    char *valor_propiedad ;
    int aux;
    printf ("Creando un fotosensor\n");
     
    /*Recorremos las propiedades del reed...*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=XMLString::transcode ( hijo->getNodeName()  );
              valor_propiedad= XMLString::transcode ( hijo->getTextContent() );
              
              /*... y aqui e extraen los valores almacenados en el XML*/
			  if (  (aux=strcmp (nombre_propiedad, "nombreelemento")) == 0 ) {
					strcpy (this->nombreelemento, valor_propiedad);
			  }
			  
			  if (  (aux=strcmp (nombre_propiedad, "entradagiro1")) == 0 ) {
					sscanf (valor_propiedad,"%f",&entradagiro1);
			  }
			  
			  if (  (aux=strcmp (nombre_propiedad, "salidagiro1")) == 0 ) {
					sscanf (valor_propiedad,"%f",&salidagiro1);
			  }
			  
			  if (  (aux=strcmp (nombre_propiedad, "entradagiro2")) == 0 ) {
					sscanf (valor_propiedad,"%f",&entradagiro2);
			  }
			  
			  if (  (aux=strcmp (nombre_propiedad, "salidagiro2")) == 0 ) {
					sscanf (valor_propiedad,"%f",&salidagiro2);
			  }
			  
			  if ( (aux=strcmp (nombre_propiedad, "entradareposo")) == 0 ) {
					sscanf (valor_propiedad,"%f",&entradaparo);
			  }
			  
			  if ( (aux=strcmp (nombre_propiedad, "salidareposo")) == 0 ) {
					sscanf (valor_propiedad,"%f",&salidaparo);
			  }
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   
}

elemento_compuesto::elemento_compuesto (DOMNode* nodo) {
}
