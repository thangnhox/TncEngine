VULKAN_FLAG = -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
GLFW_FLAG = -lglfw3
GLAD_FLAG = -lglad
CPPFLAGS = -std=c++17 -Wall
CFLAGS = -std=c17 -Wall
LIB_BUILD = -shared -fPIC
GDBFLAG = -g

DEFINE = -D DEBUG
ENABLE_ASSERT = -D ENABLE_ASSERT
GLFW_INCLUDE_NONE = -D GLFW_INCLUDE_NONE

CORE_FLAG = -lTncEngineCore

# Third party include
SPDLOG_INCLUDE = -Icore/vendore/spdlog/include
GLFW_INCLUDE = -Icore/vendore/GLFW/include
GLAD_INCLUDE = -Icore/vendore/Glad/include

# My include
CORE_INCLUDE = -Icore/src

.PHONY: core sandbox setup core_PCH test glad

# Make some empty object files in case find could not detect files in first compile
setup:
	mkdir -p bin/intermidiate bin/objectFiles/core bin/lib bin/submoduleBuild/GLFW
	touch bin/objectFiles/core/Application.o bin/objectFiles/core/Log.o bin/objectFiles/core/Window.o bin/objectFiles/core/Layer.o bin/objectFiles/core/LayerStack.o
	mkdir -p bin/objectFiles/glad
	touch bin/objectFiles/glad/glad.o
	cmake -S core/vendore/GLFW -B bin/submoduleBuild/GLFW
	cd bin/submoduleBuild/GLFW && $(MAKE) && cp src/libglfw3.a ../../lib/

core:
	g++ $(LIB_BUILD) $(CPPFLAGS) $(SPDLOG_INCLUDE) $(GLAD_INCLUDE) $(GLFW_INCLUDE) $(CORE_INCLUDE) $(ENABLE_ASSERT) -c $(shell find core/src/ -name '*.cpp')
	mv *.o bin/objectFiles/core/
	ar src bin/lib/libTncEngineCore.a $(shell find bin/objectFiles/core/ -name '*.o')

core_PCH:
	g++ $(CPPFLAGS) $(SPDLOG_INCLUDE) $(CORE_INCLUDE) core/src/TncPCH.hpp

glad:
	gcc $(CFLAGS) $(LIB_BUILD) $(GLAD_INCLUDE) -c $(shell find core/vendore/Glad/ -name '*.c')
	mv *.o bin/objectFiles/glad/
	ar src bin/lib/libglad.a $(shell find bin/objectFiles/glad/ -name '*.o')

sandbox:
	g++ -Lbin/lib $(CORE_INCLUDE) $(SPDLOG_INCLUDE) $(GLAD_INCLUDE) $(GLFW_INCLUDE) -o bin/intermidiate/SandboxApp $(shell find sandbox/src/ -name '*.cpp') $(CORE_FLAG) $(GLFW_FLAG) $(GLAD_FLAG)
