#include "domgestionerror.h"


DOMGestionError::DOMGestionError()
{
	existenErrores=false;
}
DOMGestionError::~DOMGestionError()
{
}

bool DOMGestionError::handleError(const DOMError& domError)
{
	DOMNode* nodo=domError.getLocation()->getErrorNode();
	//const char *nombreNodo=XMLString::transcode (nodo->getNodeName());
	existenErrores=true;
	const char *fich=XMLString::transcode (domError.getLocation()->getURI() );
	const char* error= XMLString::transcode ( domError.getMessage() );
	int linea = domError.getLocation()->getLineNumber();
	int columna=domError.getLocation()->getColumnNumber();
	cout << "Fichero :" << fich << endl;
	//cout << "Algo ha ocurrido en nodo" << nombreNodo;
	cout << " l:" << linea << " col:" <<columna << endl;
	if (domError.getSeverity()==DOMError::DOM_SEVERITY_WARNING)
	{
		cout << "Warning en linea " << linea ;
	}
	if (domError.getSeverity()==DOMError::DOM_SEVERITY_ERROR)
	{
		cout << "Se produjo el error:" << error <<" en linea: " <<linea;
		cout << " columna:" << columna << endl;
	}
	cout << "----------------------------------"<< endl;
}

bool DOMGestionError::hayErrores()
{
	return existenErrores;
}
