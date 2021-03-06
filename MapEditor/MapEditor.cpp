#include "stdafx.h"
#include "ForcedDeclaration.h"
#include "EditorEventReceiver.h"
#include "MenuEventReceiver.h"
#include "Render.h"
#include "Universe.h"

int main(int argc, char* argv[])
{
	Universe* universe;

	universe = new Universe();

	while (!universe->Menu())
	{
		if (universe->Run())
			break;
	}

	return 0;
}

