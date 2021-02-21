gcc															\
	-S -std=c++2a											\
	-I project/sources										\
	-I project/libraries/glad/build/include					\
	-I project/libraries/glfw/include						\
	-I project/libraries/glm								\
	-I project/libraries/stb								\
	-I project/libraries/freetype2/include					\
	-I project/libraries/FastNoise/Cpp						\
	"$1"