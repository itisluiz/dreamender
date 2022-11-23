#include <sdk/byond.hh>
#include <internals/logging/macro.hh>
#undef min
#undef max

namespace syndicate::sdk
{
	// Coords
	Coords::Coords(uint16_t x, uint16_t y)
		: x(x), y(y) { }

	uint32_t Coords::sqrDistance(const Coords& other)
	{
		int diffX{ static_cast<int>(x) - other.x };
		int diffY{ static_cast<int>(y) - other.y };

		return (diffX * diffX) + (diffY * diffY);
	}

	Coords Coords::operator-(const Coords& other)
	{
		return Coords( x - other.x, y - other.y );
	}

	Coords Coords::operator+(const Coords& other)
	{
		return Coords( x + other.x, y + other.y );
	}

	Coords Coords::operator*(const Coords& other)
	{
		return Coords(x * other.x, y * other.y);
	}

	Coords::operator bool()
	{
		return x != std::numeric_limits<uint16_t>::max();
	}

	// Cid
	Cid::Cid(Type type, uint32_t id)
		: m_type(type), m_id(id) { }

	Cid Cid::getLocalPlayer()
	{
		Cid player;
		return *byond::GetPlayerCid(&player);;
	}

	std::vector<Cid> Cid::availableCids(Type type, uint16_t maxID)
	{
		std::vector<Cid> cids;

		for (uint16_t id{ 0 }; id < maxID; ++id)
		{
			Cid cid(type, id);

			if (cid)
				cids.push_back(cid);
		}

		return cids;
	}

	Cid::Type Cid::getType() { return m_type; }
	uint32_t Cid::getID() { return m_id; }

	Coords Cid::getPos()
	{
		Coords coords[2];
		byond::GetCidLoc(coords, *this);

		return coords[1];
	}

	const char* Cid::getName()
	{	
		return byond::GetCidName(*this);
	}

	Cid::operator bool()
	{
		if (!m_id)
			return false;

		return getPos();
	}

	bool Cid::operator==(const Cid& other)
	{
		return m_type == other.m_type && m_id == other.m_id;
	}

	// Mouseparams
	MouseParams::MouseParams(Cid target, Coords pixel)
		: m_cid(target), m_pixel0(pixel), m_pixel1(pixel), m_pixel2(pixel)
	{
		m_worldTile = target.getPos();
		m_screenTile = (m_worldTile + Coords(8, 8)) - Cid::getLocalPlayer().getPos();
	}

	Cid MouseParams::getCid() { return m_cid; }
	Coords MouseParams::getWorldTile() { return m_worldTile; }
	Coords MouseParams::getScreenTile() { return m_screenTile; }
	Coords MouseParams::getPixel() { return m_pixel0; }

	void MouseParams::setCid(Cid cid) { m_cid = cid; }
	void MouseParams::setWorldTile(Coords worldTile) { m_worldTile = worldTile; }
	void MouseParams::setScreenTile(Coords screenTile) { m_screenTile = screenTile; }
	void MouseParams::setPixel(const Coords& pixel)
	{
		m_pixel0 = pixel;
		m_pixel1 = pixel;
		m_pixel2 = pixel;
	}

	// Game
	namespace byond
	{
		functional::Procedure<Cid* (__stdcall)(Cid*)> GetPlayerCid;
		functional::Procedure<void* (__stdcall)(void*, Cid)> GetCidLoc;
		functional::Procedure<const char* (__stdcall)(Cid)> GetCidName;
		functional::Procedure<bool(__stdcall)(MouseParams*)> GenClickCommand;
		functional::Procedure<bool(__stdcall)(MouseParams*, MouseParams*)> GenMouseDropCommand;
		functional::Procedure<bool(__stdcall)(MouseParams*)> GenMouseMoveCommand;
		functional::Procedure<uintptr_t*> Render;

		void init()
		{
			HMODULE byondCore{ GetModuleHandleA("byondcore.dll") };
			if (!byondCore) return;

			GetPlayerCid = GetPlayerCid.fromExport(byondCore, "?GetPlayerCid@DSStat@@QAE?AUCid@@XZ");
			GetCidLoc = GetCidLoc.fromExport(byondCore, "?GetCidLoc@DungClient@@QAE?AUCid@@U2@@Z");
			GetCidName = GetCidName.fromExport(byondCore, "?GetCidName@DungClient@@QAEPBDUCid@@@Z");
			GenClickCommand = GenClickCommand.fromExport(byondCore, "?GenClickCommand@DungClient@@QAEHABUMouseParams@@@Z");
			GenMouseDropCommand = GenMouseDropCommand.fromExport(byondCore, "?GenMouseDropCommand@DungClient@@QAEHABUMouseParams@@0@Z");
			GenMouseMoveCommand = GenMouseMoveCommand.fromExport(byondCore, "?GenMouseMoveCommand@DungClient@@QAEHABUMouseParams@@@Z");
			Render = Render.fromPattern(byondCore, { "74 20 A1 ?? ?? ?? ?? 85 C0", 3 });
		}

	}
}