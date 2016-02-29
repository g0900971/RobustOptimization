#include "ROLib.h"
#include "ROVarImpl.h"
#include "ROUnImpl.h"

bool ROLib::init()
{
	return true;
}

void ROLib::destroy()
{
	ROVarImplManager::destroy();
	ROUnImplManager::destroy();
}

