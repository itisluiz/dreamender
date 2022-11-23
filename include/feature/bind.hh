#ifndef SYNDICATE_FEATURE_BIND_H
#define SYNDICATE_FEATURE_BIND_H
#include <internals/functional/procedure.hh>

namespace syndicate::feature::bind
{
	bool init();
	bool handleBind(uint8_t keyCode);
	bool makeBind(uint8_t keyCode);

}

#endif