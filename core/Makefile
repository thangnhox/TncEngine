CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

GDBFLAGS = -g

DEFINE = -D DEBUG

SHADER_PATH = src/shaders/

Compile: *.cpp
	g++ $(CFLAGS) $(DEFINE) -o debug $(shell find . -name '*.cpp') $(LDFLAGS)

.PHONY: debug clean shader debuger debuger_build

shader:
	glslc $(shell find $(SHADER_PATH) -name '*.vert' -o -name '*.frag') -c
	mv -f *.spv $(SHADER_PATH)

debug: debug
	./debug

clean:
	rm -f debug $(shell find . -name '*.spv')

debuger:
	gdb ./debuger

debuger_build:
	g++ $(CFLAGS) $(DEFINE) -o debuger $(shell find . -name '*.cpp') $(LDFLAGS) $(GDBFLAGS)
