#ifndef _senal_
#define _senal_


#define NADA 		0
#define VOLTAJE 	1
#define LUMINOSIDAD 2
#define GIRO		3
#define MAGNETISMO	4
#define CONEXION	5
#include <string>
#include "constantes.h"

using std::string;

/*	Se fabrica una jerarquía de señales para distinguir las distintas
	señales de entrada y salida que pueden tener los distintos elementos*/

class Senal {
	public:
			virtual int getTipo() { return NADA; }
			virtual const char* toString() {return "XXXXXX";}
};

/*	Un voltaje es un tipo por derecho propio y su valor no puede 
	ser modificado. Si se es necesario se deberá crear otro voltaje*/
class Voltaje : public Senal {
	private:
		float valor;
	public:
		Voltaje (float v) {
			this->valor=v;
		}
		float getValor() 	{ return valor ; }
		void  setValor(float v)	
		{
			valor=v;
		}
		
		virtual int getTipo () 		{ return VOLTAJE; }
		const char* toString() {
			char* c=new char[5];
			sprintf (c, "%2.1f", valor);
			return c;
		}
};

/*	La luminosidad es una señal producida por la lámpara o la
	captada por un fotosensor. Se puede distinguir luminosidad
	de distintos colores*/
class Luminosidad: public Senal {
	private:
		char* color;
	public:
		Luminosidad (char* c) {
			color=new char[MAX_LONG_NOMBRE_ELEMENTO];
			strcpy (color,c);
		}
		char* getValor() 	{ return color ; }
		virtual int getTipo	()		{ return LUMINOSIDAD ; }
		const char* toString() {
			return color;
		}
};

/*	Esta clase representa el giro de un motor. Cabe destacar que si no 
	se suministra un giro válido, automáticamente se pone el movimiento
	a "stop" */
class Giro : public Senal {
	private:
		char giro[MAX_LONG_PALABRA_GIRO];
	public:
		Giro (char* c)
		{
			strcpy (giro, c);
		}
		
		char* getValor ()  { return &giro[0] ; }
		
		void setValor (char *c) {strcpy (giro,c);}
					
		virtual int getTipo()		{ return GIRO ; }
		
		const char* toString() {
			return giro;
		}
};



class Magnetismo : public Senal {
	private:
		bool valor;
	public:
		Magnetismo (bool v) { this->valor=v; }
		bool getValor () 	{ return valor; }
		virtual int getTipo ()		{ return MAGNETISMO; }
		const char* toString() {
			char* c=new char[5];
			if (valor==true) strcpy (c,"true");
			if (valor==false)strcpy (c,"false");
			return c;
		}
};

/*	Esta señal se usa en los pulsadores y en los relés indicando si
	el pulsador o un relé se ha conectado*/
class Conexion : public Senal {
	private:
		bool valor;
	public:
		Conexion (bool v) 	{ this->valor=v; }
		bool getValor ()	{ return valor; }
		virtual int getTipo ()		{ return CONEXION; }
		const char* toString() {
			char* c=new char[5];
			if (valor==true) strcpy (c,"true");
			if (valor==false)strcpy (c,"false");
			return c;
		}
};	
class Frecuencia : public Senal {
	private:
		float hercios;
	public:
		Frecuencia (float v) {
			this->hercios=v;
		}
		float getValor() 	{ return hercios ; }
		void  setValor(float v)	
		{
			hercios=v;
		}
		
		virtual int getTipo () 		{ return VOLTAJE; }
		const char* toString() {
			char* c=new char[5];
			sprintf (c, "%f", hercios);
			return c;
		}
};


#endif
