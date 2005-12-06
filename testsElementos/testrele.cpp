#include "unit++.h"
#include "rele.h"

using namespace unitpp;

namespace
{
	
	class PruebaRele: public suite
	{
		void PruebaValores()
		{	
			Conexion* c1=new Conexion (CONEXION_INACTIVA);
			Conexion* c2=new Conexion (CONEXION_ACTIVA);
			Voltaje*  v1=new Voltaje  (0.0);
			Voltaje*  v2=new Voltaje  (5.0);
			
			Rele *r=new Rele (v1,c1,v2,c2);
			
			/*	Se comprueban los valores basicos*/
			Conexion *c;
			c=r->getConexionReposo();
			assert_eq ("Valor de la conexion en reposo",
				c->getValor(), c1->getValor() );
			
			c=r->getConexionActivacion();
			assert_eq ("Valor de la conexion en activacion",
				c->getValor(), c2->getValor() );
			
			Voltaje *v;
			v=r->getVoltajeReposo();
			assert_eq ("Valor del voltaje en reposo",
				v->getValor(), v1->getValor() );
			
			v=r->getVoltajeActivacion();
			assert_eq ("Valor del voltaje en activacion",
				v->getValor(), v2->getValor() );
		}
		void PruebaPorDefecto()
		{	
			Conexion* c1=new Conexion (CONEXION_INACTIVA);
			Conexion* c2=new Conexion (CONEXION_ACTIVA);
			Voltaje*  v1=new Voltaje  (0.0);
			Voltaje*  v2=new Voltaje  (5.0);
			
			Rele *r=new Rele (v1,c1,v2,c2);
			
			/*	Probamos las entradas y salidas por defecto*/
			Voltaje *v;
			v=(Voltaje*)r->getEntradaPorPosicion();
			/*	En la entrada deberia haber el voltaje por defecto*/
			assert_eq ("Valor por defecto de la entrada correcto",
				v->getValor(), v1->getValor() );
				
			Conexion* c;
			c=(Conexion*)r->getSalidaPorPosicion();
			assert_eq ("Valor por defecto de la salida correcto",
				c->getValor(), c1->getValor() );
		}
		public:
			PruebaRele(): suite ("Prueba del sistema")
			{
				add ("Prueba Rele", testcase (this, 
					"PruebaRele", &PruebaRele::PruebaValores));
				add ("Prueba por defecto del Rele", testcase (this, 
					"PruebaPorDefectoRele", &PruebaRele::PruebaPorDefecto));
				suite::main().add ("Prueba Rele", this);
			}
	};
	
	PruebaRele* pel=new PruebaRele();	
}
