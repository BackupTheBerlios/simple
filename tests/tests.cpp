#include <cstdlib>
#include <iostream>
#include <string>

#include "elementos.h"
#include "parser.h"
#include <unit++.h>	

using namespace std;
using namespace unitpp;

//Todas las pruebas están situadas en un espacio
//de nombre anónimo y totalmente aparte
namespace {
	class pruebaParser : public suite
	{
		Parser* p;
		void pruebaFicheroTest()
		{
			p=new Parser();
			//El fichero test.xml está "diseñado" para ser valido
			//Cualquier error tiene que saltar aqui
			assert_eq ("Fichero de test", true, p->esValido("test.xml") );
			
		}
		void pruebaRecuperaElementos()
		{
			vector <elemento*> v;
			v=p->extraerElementos();
			assert_eq ("Vector vacio?", false, v.empty() );
		}
	public:
		pruebaParser() : suite ("Prueba de clase parser")
		{
			add ("Fichero de test", testcase 
				(this, "pruebaCreacion", &pruebaParser::pruebaFicheroTest));
			add ("Recuperacion de elementos", testcase 
				(this, "Recuperando elementos", &pruebaParser::pruebaRecuperaElementos));
			suite::main().add ("pruebaFicheroTest", this);
				
		}
	}; // Fin de la clase
	
	pruebaParser *laPruebaDelParser=new pruebaParser();
}
