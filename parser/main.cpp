#include <cstdlib>
#include <iostream>
//Evitar instanciación de plantillas
#define XERCES_TMPLSINC



#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/validators/common/Grammar.hpp>	
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>


#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif 

using namespace std;

class DOMGestionError : public DOMErrorHandler
{
	public:
		DOMGestionError();
		~DOMGestionError();
		bool handleError(const DOMError& domError);
		bool hayErrores();
	private:
		bool existenErrores;
};

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


int main(int argc, char *argv[])
{
	DOMDocument* documento=NULL;
	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& e)
	{
		cout << "No se pudo inicializar el parser" << endl ;
	}
	
	static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
	DOMImplementation *impl = 
		DOMImplementationRegistry::getDOMImplementation(gLS);
	if (impl==NULL) cout << "No se logro una implementacion" << endl;
    
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
	DOMErrorHandler* err=parser->getErrorHandler();
	if (err==NULL) cout << "No hay gestor de errores\n";
	
	cout << "Analizando... " <<  endl;
	const XMLCh* nombrefichero=XMLString::transcode ("proyecto.xml");
	try {
		const XMLCh* gramatica=XMLString::transcode ("sistema2.xsd");
		parser->loadGrammar(gramatica, 
			Grammar::SchemaGrammarType,true);
		//Se analiza un fichero y se recupera el objeto
		//DOMDocument que representa los elementos
		//XML que hay en el fichero
		documento=parser->parseURI (nombrefichero);
		if (documento==NULL) cout << "Error!!!" << endl;
	}
	catch (const XMLException& toCatch)
        {
            cout << "\nError during parsing: " <<"\n"
                 << "Exception message is:  \n";
            int lineaErronea= toCatch.getSrcLine();
            cout << "La linea equivocada es: "<< lineaErronea;
        }
        catch (const DOMException& toCatch)
        {
            cout << "\nDOM Error during parsing: " << "\n"
                 << "DOMException code is:  " << toCatch.code << XERCES_STD_QUALIFIER endl;
        }
    return 0;
}

