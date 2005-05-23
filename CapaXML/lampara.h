#include "elementosimple.h"

#ifndef _lampara_
#define _lampara_

class Lampara: public ElementoSimple {
	public:
		void 		construir				(DOMNode *nodo);
		XMLCh*		getColor				();
		DOMElement*	getNodo					();
	private:
		XMLCh* color;	
};



#endif
