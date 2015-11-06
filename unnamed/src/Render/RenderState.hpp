#pragma once

namespace me{

	class RenderState{
	private:
		enum{
			MaxTextures = 8
		};

		Texture* textures[MaxTextures] = {NULL};
		Program* program = NULL;
		

	};

}