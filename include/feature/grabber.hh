#ifndef SYNDICATE_FEATURE_GRABBER_H
#define SYNDICATE_FEATURE_GRABBER_H
#include <misc/algorithm.hh>

namespace syndicate::feature::grabber
{
	static uint32_t grab_hash[]
	{
		misc::const_hash("stunbaton"),
		misc::const_hash("telescopic baton"),
		misc::const_hash(".357 revolver"),
		misc::const_hash("stechkin pistol"),
		misc::const_hash("shotgun"),
		misc::const_hash("riot shotgun"),
		misc::const_hash("double-barreled shotgun"),
		misc::const_hash("'Bulldog' Shotgun"),
		misc::const_hash("combat shotgun"),
		misc::const_hash("security auto rifle"),
		misc::const_hash("laser gun"),
		misc::const_hash("DL-88 energy revolver"),
		misc::const_hash("ion rifle"),
		misc::const_hash("energy gun"),
		misc::const_hash("advanced energy gun"),
		misc::const_hash("disabler"),
		misc::const_hash("chainsaw"),
		misc::const_hash("baseball bat"),
		misc::const_hash("fire axe"),
		misc::const_hash("energy sword"),
		misc::const_hash("double-bladed energy sword"),
		misc::const_hash("energy dagger"),
		misc::const_hash("Unica 6 auto-revolver"),
		misc::const_hash("nagant revolver"),
		misc::const_hash("pulse rifle"),
		misc::const_hash("improvised shotgun"),
		misc::const_hash("spear"),
		misc::const_hash("stunprod"),
		misc::const_hash("ritual dagger"),
		misc::const_hash("cult blade"),
		misc::const_hash("mini energy crossbow"),
		misc::const_hash("energy crossbow"),
		misc::const_hash("power-fist"),
		misc::const_hash("tesla revolver"),
		misc::const_hash("plasma pistol"),
		misc::const_hash("biological demolecularisor"),
		misc::const_hash("alien pistol"),
		misc::const_hash("mounted emitter"),
		misc::const_hash("ion carbine"),
		misc::const_hash("M1911"),
		misc::const_hash("Enforcer"),
		misc::const_hash("Desert Eagle"),
		misc::const_hash("C-20r SMG"),
		misc::const_hash("Nanotrasen Saber SMG"),
		misc::const_hash("Thompson SMG"),
		misc::const_hash("'Type U3' Uzi"),
		misc::const_hash("M-90gl Carbine"),
		misc::const_hash("ARG"),
		misc::const_hash("L6 SAW"),
		misc::const_hash("B.S.G"),
		misc::const_hash("rocket launcher"),
		misc::const_hash("multi grenade launcher"),
		misc::const_hash("grenade launcher"),
		misc::const_hash("bone dagger"),
		misc::const_hash("bone spear"),
		misc::const_hash("bone axe"),
		misc::const_hash("bone pickaxe"),
		misc::const_hash("bone scythe"),
		misc::const_hash("flamethrower"),
		misc::const_hash("powered crossbow"),
		misc::const_hash("pneumatic cannon")
	};

	static const char* grab_keywords[]
	{
		"grenade"
	};


	bool grabWhitelisted();
	void grabThreaded(bool enabled);
}

#endif