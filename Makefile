VULKAN_FLAG = -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
CPPFLAGS = -std=c++17 -Wall
CFLAGS = -std=c17 -Wall
LIB_BUILD = -shared -fPIC
GDBFLAG = -g

DEFINE = -D DEBUG
ENABLE_ASSERT = -D ENABLE_ASSERT
GLFW_INCLUDE_NONE = -D GLFW_INCLUDE_NONE
TNC_DEBUG = -D TNC_DEBUG

# Libraries
GLFW_FLAG = -lglfw3
GLAD_FLAG = -lglad
CORE_FLAG = -lTncEngineCore
GL_FLAG = -lopengl32
IMGUI_FLAG = -limgui
GDI_FLAG = -lgdi32

# Third party include
SPDLOG_INCLUDE = -Icore/vendore/spdlog/include
GLFW_INCLUDE = -Icore/vendore/GLFW/include
GLAD_INCLUDE = -Icore/vendore/Glad/include
IMGUI_FRONTENDS_INCLUDE = -Icore/vendore/ImGUI/frontends
IMGUI_BACKENDS_INCLUDE = -Icore/vendore/ImGUI/backends
GLM_INCLUDE = -Icore/vendore/glm
STB_IMAGE_INCLUDE = -Icore/vendore/stb_image

# My include
CORE_INCLUDE = -Icore/src

.PHONY: core sandbox setup core_PCH test

# Makefile Variable

core_Srcs = $(wildcard core/src/*.cpp) $(wildcard core/src/**/*.cpp) $(wildcard core/src/**/**/*.cpp) core/vendore/stb_image/stb_image.cpp
core_Objs = $(foreach file,$(patsubst %.cpp,%.o,$(notdir $(core_Srcs))),bin/objectFiles/core/$(file))
core_Lib = bin/lib/libTncEngineCore.a
glad_Srcs = $(wildcard core/vendore/Glad/**/*.c)
glad_Objs = $(foreach file,$(patsubst %.c,%.o,$(notdir $(glad_Srcs))),bin/objectFiles/glad/$(file))
glad_Lib = bin/lib/libglad.a
imgui_Srcs = $(wildcard core/vendore/ImGUI/**/*.cpp)
imgui_Objs = $(foreach file,$(patsubst %.cpp,%.o,$(notdir $(imgui_Srcs))),bin/objectFiles/imgui/$(file))
imgui_Lib = bin/lib/libimgui.a

sandbox_Srcs = $(wildcard sandbox/src/*.cpp)
sandbox_Exe = bin/intermidiate/SandboxApp.exe

glfw3_Lib = bin/lib/libglfw3.a
binary_Folders = bin/intermidiate bin/submoduleBuild/GLFW bin/objectFiles/core bin/objectFiles/glad bin/objectFiles/imgui bin/lib

# Make some empty object files in case find could not detect files in first compile
setup: $(binary_Folders) $(glfw3_Lib) $(glad_Lib) $(imgui_Lib)
	@echo setup done

$(binary_Folders):
	powershell -Command mkdir $@

$(glfw3_Lib):
	powershell -Command cp core/vendore/GLFW/lib-mingw-w64/libglfw3.a $@

core: $(binary_Folders) $(core_Lib)
	@echo done

core_PCH:
	g++ $(CPPFLAGS) $(SPDLOG_INCLUDE) $(CORE_INCLUDE) core/src/TncPCH.hpp

sandbox: $(binary_Folders) $(sandbox_Exe)
	gdb $(sandbox_Exe)

$(glad_Lib): $(glad_Objs)
	ar src $@ $(glad_Objs)

$(glad_Objs):
	gcc $(GDBFLAG) $(CFLAGS) $(LIB_BUILD) $(GLAD_INCLUDE) -c $(wildcard core/vendore/Glad/**/$(patsubst %.o,%.c,$(notdir $@))) -o $@

$(imgui_Lib): $(imgui_Objs)
	ar src $@ $(imgui_Objs)

$(imgui_Objs):
	g++ $(GDBFLAG) $(CPPFLAGS) $(LIB_BUILD) $(GLFW_INCLUDE) $(IMGUI_FRONTENDS_INCLUDE) $(IMGUI_BACKENDS_INCLUDE) -c $(wildcard core/vendore/ImGUI/**/$(patsubst %.o,%.cpp,$(notdir $@))) -o $@

$(sandbox_Exe): $(glfw3_Lib) $(glad_Lib) $(imgui_Lib) $(core_Lib) $(sandbox_Srcs)
	$(info $(notdir $@))
	@g++ $(GDBFLAG) $(CPPFLAGS) -Lbin/lib $(CORE_INCLUDE) $(SPDLOG_INCLUDE) $(GLAD_INCLUDE) $(IMGUI_FRONTENDS_INCLUDE) $(GLFW_INCLUDE) $(IMGUI_BACKENDS_INCLUDE) $(GLM_INCLUDE) $(STB_IMAGE_INCLUDE) -o $@ $(sandbox_Srcs) $(CORE_FLAG) $(GLFW_FLAG) $(GLAD_FLAG) $(IMGUI_FLAG) $(GL_FLAG) $(GDI_FLAG)

$(core_Lib) : $(core_Objs)
	$(info $(notdir $@))
	@ar src $@ $(core_Objs)

define CORE_COMPILE
bin/objectFiles/core/$$(patsubst %.cpp,%.o,$$(notdir $(1))) : $(1) $(patsubst %.cpp,%.hpp,$(1))
	$$(info $$(notdir $(1)))
	@g++ $$(GDBFLAG) $$(LIB_BUILD) $$(CPPFLAGS) $$(SPDLOG_INCLUDE) $$(GLAD_INCLUDE) $$(CORE_INCLUDE) $$(GLFW_INCLUDE) $$(IMGUI_FRONTENDS_INCLUDE) $$(IMGUI_BACKENDS_INCLUDE) $$(GLM_INCLUDE) $$(STB_IMAGE_INCLUDE) $$(TNC_DEBUG) -c $$< -o $$@
endef

$(foreach src,$(core_Srcs),$(eval $(call CORE_COMPILE,$(src))))
