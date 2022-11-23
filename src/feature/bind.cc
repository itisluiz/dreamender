#include <feature/bind.hh>
#include <internals/logging/macro.hh>
#include <sdk/byond.hh>
#include <misc/keyhelper.hh>

namespace syndicate::feature::bind
{
	static std::map<uint8_t, sdk::Cid> binds;
	static sdk::Cid lastHoveredCid;

	functional::Procedure<bool(__stdcall)(sdk::MouseParams*)> tp_GenMouseMoveCommand;
	bool __stdcall hk_GenMouseMoveCommand(sdk::MouseParams* params)
	{
		lastHoveredCid = params->getCid();
		return tp_GenMouseMoveCommand(params);
	}

	bool handleBind(uint8_t keyCode)
	{
		if (binds.find(keyCode) == binds.end())
			return false;

		// Why does this have to happen, I wonder
		static sdk::MouseParams bindParams;
		bindParams = sdk::MouseParams(binds[keyCode]);

		return sdk::byond::GenClickCommand(&bindParams);
	}

	bool makeBind(uint8_t keyCode)
	{
		if (!lastHoveredCid.getID())
			return false;

		binds[keyCode] = lastHoveredCid;
		LOG_INFO("Bound " << dye::light_blue(lastHoveredCid.getName()) << " to " << dye::bright_white(misc::getKeyName(keyCode)));
		return true;
	}

	bool init()
	{
		tp_GenMouseMoveCommand = sdk::byond::GenMouseMoveCommand.detourTo(hk_GenMouseMoveCommand);
		
		return tp_GenMouseMoveCommand;
	}

}