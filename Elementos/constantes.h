#ifndef _constantes_
#define _constantes_

/*	Comentar las siguientes linea cuando se desee eliminar la informacion
	extra añadida para la depuracion*/
//#define DEBUG 
//#define DEBUG_CONTADOR
//#define DEBUG_MOTOR
//#define DEBUG_BIESTABLE
//#define DEBUG_PULSADOR
//#define DEBUG_LAMPARA
//#define DEBUG_SISTEMA

/*	Se pueden construir elementos del tamaño que se desee
	aunque para simplificar se han puesto estos maximos*/
#define MAX_LONG_VECTOR_ENTRADAS 75
#define MAX_LONG_VECTOR_SALIDAS	 75


/*	Una parte de estas entradas se reservan a las usadas por 
	las entradas clásicas de todo elemento, en concreto, las siguientes*/

#define POS_ENABLE 	0 	/*Para habilitar un elemento*/
#define POS_RESET	1	/*Para reinicializar un elemento*/
#define POS_KEEP	2	/*Para forzarlo a que conserve el estado*/

/*	En el vector de entradas la primera entrada "util" es esta*/
const int POS_ENTRADA=3;

/*	En el vector de salidas la primera salida "util" es esta*/
const int POS_SALIDA=0;

/*	Numero maximo de elementos que un elemento puede tener conectados*/
#define MAX_SUSCRIPCIONES 150	

/*	Longitud maxima del nombre de un elemento*/
#define MAX_LONG_NOMBRE_ELEMENTO	30

#define POS_ENTRADA_INVALIDA	-10
#define POS_SALIDA_INVALIDA		-20
#define ELEMENTO_INVALIDO		-30
#define DEMASIADAS_SUSCRIPCIONES -40
#define TIPOS_NO_COINCIDEN		-50
#define ERROR_DE_BIESTABLE		-55
#define ELEMENTO_NO_ENCONTRADO	-60
#define SUSCRIPCION_BORRADA		10
#define SUSCRIPCION_NO_EXISTIA	-65
const bool CONEXION_ACTIVA=true;
const bool CONEXION_INACTIVA=false;

#define VOLTAJE_ACTIVO		5.0
#define VOLTAJE_INACTIVO	0.0

#define MAX_NUM_ELEMENTOS_POR_SISTEMA 100

/* La diferencia entre dos float debe ser menor que este valor*/
#define MARGEN_ACEPTABLE 0.01

/*	Longitud maxima que puede tener una palabra para hablar del giro
	de un motor. En general se usa "stop" "cw" y "ccw" asi que 5 suele bastar*/
#define MAX_LONG_PALABRA_GIRO 5

#endif
