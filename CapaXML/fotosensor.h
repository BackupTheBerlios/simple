#include "elementosimple.h"
#include "constantes.h"

#ifndef _fotosensor_
#define _fotosensor_

class FotoSensor: public ElementoSimple {
	public:
		virtual DOMElement*		getNodo();
};


#endif
