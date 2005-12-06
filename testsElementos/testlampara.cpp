#include "unit++.h"
#include "lampara.h"

using namespace unitpp;

namespace
{
	class PruebaLampara: public suite
	{
		void PruebaValoresLampara()
		{
			Voltaje*	v1=new Voltaje (0.0);
			Voltaje*	v2=new Voltaje (5.0);
			Luminosidad*l1=new Luminosidad("OFF");
			Luminosidad*l2=new Luminosidad("Rojo");
			
			Lampara* lamp=new Lampara(v1,l1,v2,l2);
			
			Voltaje* v;
			Voltaje* w;
			Luminosidad *l;
			Luminosidad *m;
			
			v=lamp->getVoltajeReposo();
			w=lamp->getVoltajeActivacion();
			l=lamp->getLuminosidadReposo();
			m=lamp->getLuminosidadActivacion();
			
			assert_eq ("Voltaje de reposo en lampara", 
				v->getValor(), 0.0 );
			assert_eq ("Voltaje de activacion en lampara",
				w->getValor(), 5.0 );
				
			assert_eq ("Luminosidad en reposo de la lampara",
				l->getValor(), l1->getValor() );
			assert_eq ("Luminosidad de activacion en la lampara", 
				m->getValor(), l2->getValor() );	
		}
		public:
			PruebaLampara(): suite ("Prueba Lampara")
			{
				add ("PruebaValoresLampara", testcase (this, 
				"PruebaValoresLampara",&PruebaLampara::PruebaValoresLampara) );
				suite:main().add("PruebaLampara",this);
			}
	};
	
	PruebaLampara* prueba=new PruebaLampara();
	
	
}
