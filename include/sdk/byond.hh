#ifndef SYNDICATE_SDK_BYOND_H
#define SYNDICATE_SDK_BYOND_H
#include <cstdint>
#include <limits>
#include <vector>
#include <internals/functional/procedure.hh>

namespace syndicate::sdk
{
	struct Sight
	{
		uint16_t sight;
		uint16_t unkn0;
		uint8_t see_infrared;
		uint8_t see_in_dark;
		uint8_t see_invisible;
	};

	struct Coords
	{
		uint16_t x;
		uint16_t y;

	public:
		Coords(uint16_t x = 0, uint16_t y = 0);

	public:
		uint32_t sqrDistance(const Coords& other);

	public:
		Coords operator-(const Coords& other);
		Coords operator+(const Coords& other);
		Coords operator*(const Coords& other);
		operator bool();

	};

	class Cid
	{
	public:
		enum Type : uint16_t
		{
			typeNone = 0,
			typeMob = 1,
			typeObject = 2,
			typeTurf = 3
		};

	private:
		Type m_type;
		uint32_t m_id;

	public:
		Cid(Type type = typeNone, uint32_t id = 0);
		static Cid getLocalPlayer();
		static std::vector<Cid> availableCids(Type type, uint16_t maxID = 8196);

	public:
		Type getType();
		uint32_t getID();
		Coords getPos();
		const char* getName();

	public:
		operator bool();
		bool operator==(const Cid& other);

	};

	class MouseParams
	{
		Cid m_cid;
		uint32_t m_unkn0{ 0 };
		uint32_t m_unkn1{ 0 };
		uint32_t m_unkn2{ 0x2010101 };
		const char* m_window{ "mapwindow.map" };
		uint32_t m_unkn4{ 0 };
		Coords m_worldTile;
		Coords m_pixel0;
		Coords m_pixel1;
		Coords m_screenTile;
		Coords m_pixel2;
		uint32_t m_unkn5{ 0 };
		uint32_t m_unkn6{ 0 };

	public:
		MouseParams() = default;
		MouseParams(Cid target, Coords pixel = Coords(16, 16));

	public:
		Cid getCid();
		Coords getWorldTile();
		Coords getScreenTile();
		Coords getPixel();

		void setCid(Cid cid);
		void setWorldTile(Coords worldTile);
		void setScreenTile(Coords screenTile);
		void setPixel(const Coords& pixel);
	};

	namespace byond
	{
		extern functional::Procedure<Cid* (__stdcall)(Cid*)> GetPlayerCid;
		extern functional::Procedure<void* (__stdcall)(void*, Cid)> GetCidLoc;
		extern functional::Procedure<const char* (__stdcall)(Cid)> GetCidName;
		extern functional::Procedure<bool(__stdcall)(MouseParams*)> GenClickCommand;
		extern functional::Procedure<bool(__stdcall)(MouseParams*, MouseParams*)> GenMouseDropCommand;
		extern functional::Procedure<bool(__stdcall)(MouseParams*)> GenMouseMoveCommand;
		extern functional::Procedure<uintptr_t*> Render;

		void init();
	}

}

#endif
