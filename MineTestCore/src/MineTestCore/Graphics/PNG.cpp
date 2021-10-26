
#include "../../../includes/MineTestCore/Graphics/PNG.hpp"
#include "../includes/MineTestCore/ResourceManager/stb_image.hpp"

namespace MineTest {

	const int PNG_size = 20;

	enum class PNGtype{RGB = STBI_rgb, RGBA = STBI_rgb_alpha};

	struct PNG {
		int _w;
		int _h;
		char* _data;
		PNGtype _type;
	};

}
