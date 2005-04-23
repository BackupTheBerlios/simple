#include "elementos.h"
#include <iostream>

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
