#include "motor.h"
#include "unit++.h"

using namespace unitpp;
using namespace std;
namespace
{
	class PruebaMotor: public suite
	{
		void PruebaValoresMotor()
		{
			Voltaje*	vReposo	=	new Voltaje (0.0);
			Voltaje*	vGiroCW	=	new	Voltaje (5.0);
			Voltaje*	vGiroCCW=	new Voltaje (-5.0);

			Giro*	giroReposo	=	new Giro ("stop");
			Giro*	giroCW		= 	new Giro ("cw");
			Giro*	giroCCW		=	new Giro ("ccw");
			
			unsigned int rpm=1200;
			
			Motor* m=new Motor(vReposo,giroReposo,vGiroCW,giroCW,
				vGiroCCW, giroCCW, rpm);
			
			/*	Comprobamos si los valores se quedan en el motor*/
			
			Voltaje *vActual;
			Giro	*gActual;

			vActual=(Voltaje*)m->getEntradaPorPosicion();
			assert_eq ("Voltaje en reposo del motor",
				vReposo->getValor(), vActual->getValor() );
			
			gActual=(Giro*) m->getSalidaPorPosicion();
			assert_eq ("Giro en reposo del motor",
				giroReposo->getValor(), gActual->getValor() );
			
			unsigned int velocidad=m->getRPM();
			assert_eq ("Velocidad rpm", rpm, velocidad);
			
			
			/*	Probamos a cambiar las entradas*/
			
			/*	¿El motor gira en sentido cw?*/
			m->setEntrada(vGiroCW);
			gActual=(Giro*) m->getSalidaPorPosicion();
			assert_eq ("Giro en sentido horario del motor",
				giroCW->getValor(), gActual->getValor() );
			
			/*	¿El motor gira en sentido ccw?*/
			m->setEntrada(vGiroCCW);
			gActual=(Giro*) m->getSalidaPorPosicion();
			assert_eq ("Giro en sentido anti-horario del motor",
				giroCCW->getValor(), gActual->getValor() );
			
		}
		void PruebaGetters()
		{
			Voltaje*	vReposo	=	new Voltaje (0.0);
			Voltaje*	vGiroCW	=	new	Voltaje (5.0);
			Voltaje*	vGiroCCW=	new Voltaje (-5.0);

			Giro*	giroReposo	=	new Giro ("stop");
			Giro*	giroCW		= 	new Giro ("cw");
			Giro*	giroCCW		=	new Giro ("ccw");
			
			unsigned int rpm=1200;
			
			Motor* m=new Motor(vReposo,giroReposo,vGiroCW,giroCW,
				vGiroCCW, giroCCW, rpm);
			
			/*	Comprobamos los voltajes con los getter*/
			Voltaje* v;
			
			v=m->getVoltajeReposo();
			assert_eq ("Voltaje en reposo con getter",
				vReposo->getValor(), v->getValor() );
			
			v=m->getVoltajeGiroCW();
			assert_eq("Voltaje en CW con getter",
				vGiroCW->getValor(), v->getValor() );
			
			v=m->getVoltajeGiroCCW();
			assert_eq ("Voltaje en CCW con getter",
				vGiroCCW->getValor(), v->getValor() );
			
			/*	Comprobamos los giros con los getter*/
			Giro* g;
			int codigo_comparacion;
			
			g=m->getGiroReposo();
			#ifdef DEBUG_MOTOR
			cout << "Giro en reposo es " << g->getValor() << endl;
			#endif
			codigo_comparacion=strcmp(giroReposo->getValor(), g->getValor());
			assert_eq("Giro en reposo con getter",0, codigo_comparacion );
			
			g=m->getGiroCW();
			#ifdef DEBUG_MOTOR
			cout << "Giro en CW es " << g->getValor() << endl;
			#endif
			codigo_comparacion=strcmp(giroCW->getValor(), g->getValor());
			assert_eq("Giro en CW con getter",0, codigo_comparacion);
			
			g=m->getGiroCCW();
			#ifdef DEBUG_MOTOR
			cout << "Giro en CCW es " << g->getValor() << endl;
			#endif
			codigo_comparacion=strcmp(giroCCW->getValor(), g->getValor());
			assert_eq("Giro en CCW con getter",0, codigo_comparacion);
		}
		public:
			PruebaMotor():suite ("Prueba del motor")
			{
				add ("Prueba de valores del motor", testcase 
					(this, "PruebaValores motor", 
					&PruebaMotor::PruebaValoresMotor));
				add ("Prueba de los metodos getter", testcase 
					(this, "Prueba de getters", 
					&PruebaMotor::PruebaGetters));
			
				suite::main().add("PruebaMotores", this);	
			}
	}; /*Fin de la clase*/
	
	PruebaMotor *pMotor=new PruebaMotor();
}
