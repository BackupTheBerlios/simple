#include "zumbador.h"
#include "pulsador.h"
#include "unit++.h"

using namespace unitpp;
namespace
{
	class PruebaZumbador: public suite
	{
		void PruebaValores()
		{
			Voltaje 	*vReposo	=	new Voltaje(0.0);
			Frecuencia	*fReposo	=	new Frecuencia (0);
			Voltaje		*vActivacion=	new Voltaje (5.0);
			Frecuencia	*fActivacion=	new	Frecuencia (3000);

			Zumbador *z=new Zumbador (vReposo, fReposo, 
				vActivacion, fActivacion);
				
			Voltaje *vLeido;
			
			vLeido=z->getVoltajeReposo();
			assert_eq ("Voltaje en reposo", 0.0, vLeido->getValor() );
			
			vLeido=z->getVoltajeActivacion();
			assert_eq ("Voltaje en activacion", 5.0, vLeido->getValor() );
			
			Frecuencia *fLeida;
			
			fLeida=z->getFrecuenciaReposo();
			assert_eq ("Frecuencia en reposo", 0, fLeida->getValor());
			
			fLeida=z->getFrecuenciaActivacion();
			assert_eq ("Frecuencia en activacion", 3000, fLeida->getValor());
			
		}
		
		void PruebaPulsadorConZumbador()
		{
			/*	Creamos el pulsador */
			Conexion* c1=new Conexion (CONEXION_INACTIVA);
			Conexion* c2=new Conexion (CONEXION_ACTIVA);
			Voltaje*  v1=new Voltaje  (0.0);
			Voltaje*  v2=new Voltaje  (5.0);
			
			Pulsador* p=new Pulsador(c1,v1,c2,v2);
			
			/*	Creamos el zumbador que ira conectado a el*/
			Voltaje 	*vReposo	=	new Voltaje(0.0);
			Frecuencia	*fReposo	=	new Frecuencia (0);
			Voltaje		*vActivacion=	new Voltaje (5.0);
			Frecuencia	*fActivacion=	new	Frecuencia (3000);

			Zumbador *z=new Zumbador (vReposo, fReposo, 
				vActivacion, fActivacion);
			
			/*	El zumbador "escuchara" la salida del pulsador*/
			p->anadirSuscriptor(z);
			
			/*	Cambiamos las entradas y examinamos las salidas*/
			
			p->setEntrada(c2);
			
			Frecuencia *fLeida;
			fLeida=(Frecuencia*)z->getSalidaPorPosicion();
			assert_eq ("Frecuencia en pulsacion", 3000, fLeida->getValor());
			
			/*	Volvemos a cambiar la entrada del pulsador, desactivando*/
			p->setEntrada(c1);
			
			fLeida=(Frecuencia*)z->getSalidaPorPosicion();
			assert_eq ("Frecuencia en no pulsacion", 0, fLeida->getValor());
		}
		public:
			PruebaZumbador(): suite ("Prueba del zumbador")
			{
				add ("Prueba Zumbador", testcase (this, 
					"PruebaZumbador", &PruebaZumbador::PruebaValores));
				add ("Prueba Pulsador-Zumbador", testcase (this, 
					"Prueba Pulsador-Zumbador", 
					&PruebaZumbador::PruebaPulsadorConZumbador));
				suite::main().add ("Prueba Zumbador", this);
			}
	};
	
	PruebaZumbador *pZumbar=new PruebaZumbador();	
}
