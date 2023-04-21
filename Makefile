VULKAN_FLAG = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
CFLAGS = -std=c++17 -Wall
LIB_BUILD = -shared -fPIC
GDBFLAG = -g

DEFINE = -D DEBUG

# Third party library
SPDLOG_INCLUDE = -Icore/vendore/spdlog/include

# My library
CORE_INCLUDE = -Icore/src

.PHONY: core sandbox

core:
	g++ $(LIB_BUILD) $(CFLAGS) $(GDBFLAG) $(SPDLOG_INCLUDE) -c $(shell find core/src/ -name '*.cpp')
	mv *.o bin/objectFiles/core/
	ar src bin/lib/libTncEngineCore.a $(shell find bin/objectFiles/core/ -name '*.o')

sandbox:
	g++ -Lbin/lib $(CORE_INCLUDE) $(SPDLOG_INCLUDE) -o bin/intermidiate/SanboxApp $(shell find sandbox/src/ -name '*.cpp') -lTncEngineCore