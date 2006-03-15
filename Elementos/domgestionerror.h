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
#include <iostream>
using namespace std;

#ifndef _domgestionerror_
#define _domgestionerror_


/*	Esta clase es llamada cuando el parser detecta un error.
	Se limita a tomar nota de si hay errores o no para así avisar
	al usuario */
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
#endif
