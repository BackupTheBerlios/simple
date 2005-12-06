#include "unit++.h"
#include "pulsador.h"
#include "contador.h"

using namespace unitpp;

namespace
{
	
	class PruebaPulsador : public suite
	{
		void PruebaValoresPulsador()
		{
			Conexion* c1=new Conexion (CONEXION_INACTIVA);
			Conexion* c2=new Conexion (CONEXION_ACTIVA);
			Voltaje*  v1=new Voltaje  (0.0);
			Voltaje*  v2=new Voltaje  (5.0);
			
			Pulsador* p=new Pulsador(c1,v1,c2,v2);
			
			Conexion *d;
			Conexion *e;
			Voltaje  *v;
			Voltaje  *w;
			
			d=p->getConexionReposo();
			e=p->getConexionActivacion();
			
			v=p->getVoltajeReposo();
			w=p->getVoltajeActivacion();
			
			assert_eq ("Conexion en reposo", d->getValor(), c1->getValor() );
			assert_eq ("Conexion activa", 	 e->getValor(), c2->getValor() );
			
			assert_eq ("Voltaje en reposo",  v->getValor(), v1->getValor() );
			assert_eq ("Voltaje activacion", w->getValor(), v2->getValor() );				
		}
		
		
		public:
			PruebaPulsador() : suite ("Prueba de los pulsadores")
			{
				add ("PruebaValoresPulsador", testcase (this,
					"PruebaValoresPulsador", 
					&PruebaPulsador::PruebaValoresPulsador) );
				
				suite::main().add("PruebaPulsador", this);
			}
	};
	PruebaPulsador *p=new PruebaPulsador();	
}
