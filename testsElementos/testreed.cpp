#include "unit++.h"
#include "reed.h"
#include "electroiman.h"

using namespace unitpp;

namespace
{
	class PruebaReed: public suite
	{
		void PruebaValoresReed()
		{
			Magnetismo *m1=new Magnetismo(false);
			Magnetismo *m2=new Magnetismo(true);
			Conexion   *c1=new Conexion (false);
			Conexion   *c2=new Conexion (true);
			
			Reed* r1=new Reed(m1,c1,m2,c2);
			
			Magnetismo *mLeido=r1->getMagnetismoReposo();
			
			assert_eq ("Magnetismo en reposo del reed",
				m1->getValor(), mLeido->getValor() );
			
			mLeido=r1->getMagnetismoActivacion();
			assert_eq ("Magnetismo en activacion del reed",
				m2->getValor(), mLeido->getValor() );
				
			Conexion *cLeida=r1->getConexionReposo();
			assert_eq ("Magnetismo en reposo del reed",
				c1->getValor(), cLeida->getValor() );
			
			cLeida=r1->getConexionActivacion();
			assert_eq ("Magnetismo en reposo del reed",
				c2->getValor(), cLeida->getValor() );
		}
		
		void PruebaLecturaMetodosVirtuales()
		{
			Magnetismo *m1=new Magnetismo(false);
			Magnetismo *m2=new Magnetismo(true);
			Conexion   *c1=new Conexion (false);
			Conexion   *c2=new Conexion (true);
			
			Reed* r1=new Reed(m1,c1,m2,c2);
			
			Magnetismo 	*mLeido=(Magnetismo*)r1->getEntradaPorPosicion();
			Conexion	*cLeida=(Conexion*)  r1->getSalidaPorPosicion();
			/*	En principio los valores leidos deben ser los de reposo*/
			assert_eq ("Magnetismo en reposo (metodo virtual)",
				m1->getValor(), mLeido->getValor() );
			assert_eq ("Conexion en reposo (metodo virtual)", 
				c1->getValor(), cLeida->getValor() );
		}
		void PruebaConexionAElectroiman()
		{
			/*Creamos el reed*/
			Magnetismo *m1=new Magnetismo(false);
			Magnetismo *m2=new Magnetismo(true);
			Conexion   *c1=new Conexion (false);
			Conexion   *c2=new Conexion (true);
			
			Reed* r1=new Reed(m1,c1,m2,c2);
			
			/*Creamos el electroiman*/
			
			Voltaje* vReposo		=	new Voltaje (0.0);
			Voltaje* vActivacion	=	new Voltaje(5.0);
			Magnetismo* mReposo		=	new Magnetismo (false);
			Magnetismo* mActivacion	=	new Magnetismo (true);
			
			Electroiman* e			=	new Electroiman(vReposo, vActivacion,
				mReposo, mActivacion);
				
			/*	El reed está a la escucha del electroiman*/
			e->anadirSuscriptor(r1);
			
			/*	Y al modificar la entrada del electroiman...*/
			e->setEntrada(vActivacion);
			
			/*	...la salida del reed deberia haber cambiado y estar activa*/
			Conexion *cReed=(Conexion*) r1->getSalidaPorPosicion();
			
			assert_eq("Conexion electroiman a reed",
				c2->getValor(), cReed->getValor() );
			
			/*	Dejamos el electroiman como estaba...*/
			e->setEntrada(vReposo);
			
			/*	...y el reed deberia desactivarse*/
			cReed=(Conexion*)r1->getSalidaPorPosicion();
			assert_eq("Conexion electroiman a reed",
				c1->getValor(), cReed->getValor() );
			
		}
		public:
		PruebaReed(): suite ("Prueba de los reed")
		{
			add ("Prueba Valores del reed", testcase 
			(this, "PruebaPulsadorBiestableLampara", 
			&PruebaReed::PruebaValoresReed));
			
			add ("Prueba metodos virtuales", testcase 
			(this, "PruebaLecturaMetodosVirtuales", 
			&PruebaReed::PruebaLecturaMetodosVirtuales));
			
			add ("Prueba de conexion con electroiman", testcase 
			(this, "PruebaConexionAElectroiman", 
			&PruebaReed::PruebaConexionAElectroiman));
			
			suite::main().add("PruebaConexiones", this);	
		}
	};
	
	PruebaReed *pReed=new PruebaReed();	
}
