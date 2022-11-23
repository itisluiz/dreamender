#ifndef SYNDICATE_FEATURE_XRAY_H
#define SYNDICATE_FEATURE_XRAY_H
#include <internals/functional/procedure.hh>

namespace syndicate::feature::xray
{
	bool init(uint8_t enable);
	void cycleMode();
}

#endif