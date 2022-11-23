#ifndef SYNDICATE_FUNCTIONAL_DETOURMANAGER_H
#define SYNDICATE_FUNCTIONAL_DETOURMANAGER_H

namespace syndicate::functional
{
	class DetourManager
	{
	public:
		static bool setup(bool init);
		static void* create(void* target, void* callback, bool enable = true);
		static bool remove(void* target);
		static bool enabled(void* target, bool enable);

	};

}

#endif
