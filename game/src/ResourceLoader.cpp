#include "ResourceLoader.h"

Font ResourceLoader::LoadFontRes()
{
	return LoadFontEx("resources/Fonts/blocks.ttf", 128, NULL, 0);
}
