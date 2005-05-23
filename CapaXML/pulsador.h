#include "elementosimple.h"
#include "constantes.h"
#ifndef _pulsador_
#define _pulsador_

class Pulsador: public ElementoSimple {
      public:
             virtual DOMElement* 	getNodo();
};

#endif
