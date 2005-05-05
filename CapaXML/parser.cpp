#include "parser.h"

using namespace std;
/*Se construye un parser a partir de un fichero dado*/
Parser::Parser () 
{
	/*Se intenta inicializar el subsistema XML*/
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& tocatch) {
		cout << "Error!" <<endl ;
	}
	
	//Observese que en gLS hay la cadena "LS\0" (null al final)
	//La cadena se tiene que fabricar asi porque Xerces usa 
	//caracteres de ancho largo (XMLCh's)
	
	//La cadena LS significa Load and Save, y permite obtener un 
	//DOMParser que pueda leer y salvar XML's
	
	
	//En Xerces 2.4 esta forma de obtener una DOMImplementation
	//es experimental y podria cambiar en otras versiones
	static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
	DOMImplementation *impl = 
		DOMImplementationRegistry::getDOMImplementation(gLS);
	if (impl==NULL) cout << "No se logro una implementacion" << endl;
    
	//Un DOMBuilder puede parsear XML's y construir el arbol DOM asociado
	//Tambien experimental
	parser = 
		((DOMImplementationLS*)impl)->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
	
	//Puede que necesitemos usar los espacios de nombres	
	parser->setFeature(XMLUni::fgDOMNamespaces, true);
	//Se va a usar validacion mediante Schemas
    parser->setFeature(XMLUni::fgXercesSchema, true);
    
    //Se va a usar la validación exhaustiva de Schemas
    //Estas comprobaciones extras pueden consumir mucha memoria
    //o recursos pero solo lo hacemos una vez (merece la pena)
    parser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);
}
bool Parser::esValido(const char* fichero){
	const XMLCh* nombrefichero;
	
	nombrefichero=XMLString::transcode (fichero);
	try {
		
		//Se analiza un fichero y se recupera el objeto
		//DOMDocument que representa los elementos
		//XML que hay en el fichero
		documento=parser->parseURI (nombrefichero);
	}
	catch (const XMLException& toCatch)
        {
            XERCES_STD_QUALIFIER cerr << "\nError during parsing: '" << fichero << "'\n"
                 << "Exception message is:  \n";
        }
        catch (const DOMException& toCatch)
        {
            XERCES_STD_QUALIFIER cerr << "\nDOM Error during parsing: '" << fichero << "'\n"
                 << "DOMException code is:  " << toCatch.code << XERCES_STD_QUALIFIER endl;
        }
	return true;
}

vector <elemento*> Parser::extraerElementos ()
{
	vector<elemento*> vector_elementos (50);
	/*	Cuando se llama a este método ya se dispone de un objeto DOMDocument
		almacenado en "documento", por lo que podemos acceder a los elementos
		XML almacenados*/
		
		/*Obtenemos el nodo raiz que contiene a todos los demas*/
		DOMNode*	raiz; 
		raiz=(DOMNode*) documento->getDocumentElement();
		
		/*Vamos al primer hijo...*/
		DOMNode*	primer_elemento;
		primer_elemento= raiz->getFirstChild();
		
		/*...y recorremos todos los hijos*/
		DOMNode*	elemento_siguiente=primer_elemento;
		while (elemento_siguiente!=NULL)
		{
			if (elemento_siguiente->getNodeType()==DOMNode::ELEMENT_NODE)
			{
				char* nombre=XMLString::transcode
					(elemento_siguiente->getNodeName());
				if (XMLString::equals (nombre, "motor"))
				{
					motor *m=new motor();
					m->construir (elemento_siguiente);
					vector_elementos.push_back(m);
				}
			}
			
			elemento_siguiente=elemento_siguiente->getNextSibling();
		}
}


Parser::~Parser()
{
	delete elParser;
	delete manejador;
	XMLPlatformUtils::Terminate();
}
