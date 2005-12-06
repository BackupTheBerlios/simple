#include "parser.h"
#include "domgestionerror.h"
#include <iostream>

using namespace std;

Parser::Parser()
{
	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& e)
	{
	}
	
	static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
	DOMImplementation *impl = 
		DOMImplementationRegistry::getDOMImplementation(gLS);
	if (impl==NULL) {
		cout << "No se logro una implementacion" << endl;
	}
    
    DOMBuilder* parser = 
		((DOMImplementationLS*)impl)->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
	//Puede que necesitemos usar los espacios de nombres	
	parser->setFeature(XMLUni::fgDOMNamespaces, true);
	//Se va a usar validacion mediante Schemas
    parser->setFeature(XMLUni::fgXercesSchema, true);
	parser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);
	parser->setFeature(XMLUni::fgDOMValidation, true);
	// enable datatype normalization - default is off
    parser->setFeature(XMLUni::fgDOMDatatypeNormalization, true);
	parser->setErrorHandler (new DOMGestionError);
}

void Parser::extraerElementos(const char* fichero)
{
	DOMDocument* documento;
	const XMLCh* nombreFichero=XMLString::transcode(fichero);
	errorHandler.resetErrors();
}
