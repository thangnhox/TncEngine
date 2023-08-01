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
GLFW_FLAG = -lglfw
GLAD_FLAG = -lglad
CORE_FLAG = -lTncEngineCore
GL_FLAG = -lGL
IMGUI_FLAG = -limgui

# Third party include
SPDLOG_INCLUDE = -Icore/vendore/spdlog/include
GLAD_INCLUDE = -Icore/vendore/Glad/include
IMGUI_FRONTENDS_INCLUDE = -Icore/vendore/ImGUI/frontends
IMGUI_BACKENDS_INCLUDE = -Icore/vendore/ImGUI/backends
GLM_INCLUDE = -Icore/vendore/glm

# My include
CORE_INCLUDE = -Icore/src

.PHONY: core sandbox setup core_PCH test glad imgui

# Makefile Variable
core_Srcs = $(shell find core/src/ -name '*.cpp')
core_Objs = $(foreach file,$(patsubst %.cpp,%.o,$(notdir $(core_Srcs))),bin/objectFiles/core/$(file))
glad_Srcs = $(shell find core/vendore/Glad/ -name '*.c')
glad_Objs = $(foreach file,$(patsubst %.c,%.o,$(notdir $(glad_Srcs))),bin/objectFiles/glad/$(file))
imgui_Srcs = $(shell find core/vendore/ImGUI/ -name '*.cpp')
imgui_Objs = $(foreach file,$(patsubst %.cpp,%.o,$(notdir $(imgui_Srcs))),bin/objectFiles/imgui/$(file))
sandbox_Srcs = $(shell find sandbox/src/ -name '*.cpp')

# Make some empty object files in case find could not detect files in first compile
setup: init_Folders init_Dependency_Packages glad imgui
	$(info setup done)

init_Folders:
	mkdir -p bin/intermidiate bin/objectFiles/core bin/lib
	mkdir -p bin/objectFiles/glad
	mkdir -p bin/objectFiles/imgui

init_Dependency_Packages:
	pkg upgrade -y
	pkg install mesa-dev glfw opengl -y

core: $(core_Objs)
	ar src bin/lib/libTncEngineCore.a $(core_Objs)

core_PCH:
	g++ $(CPPFLAGS) $(SPDLOG_INCLUDE) $(CORE_INCLUDE) core/src/TncPCH.hpp

glad:
	@$(foreach file,$(glad_Srcs),\
	echo "Compiling $(file)";\
	gcc $(GDBFLAG) $(CFLAGS) $(LIB_BUILD) $(GLAD_INCLUDE) -c $(file) -o bin/objectFiles/glad/$(patsubst %.c,%.o,$(notdir $(file)));)
	ar src bin/lib/libglad.a $(glad_Objs)

imgui:
	@$(foreach file,$(imgui_Srcs),\
	echo "Compiling $(file)";\
	g++ $(GDBFLAG) $(CPPFLAGS) $(LIB_BUILD) $(IMGUI_FRONTENDS_INCLUDE) $(IMGUI_BACKENDS_INCLUDE) -c $(file) -o bin/objectFiles/imgui/$(patsubst %.cpp,%.o,$(notdir $(file)));)
	ar src bin/lib/libimgui.a $(imgui_Objs)

sandbox:
	g++ $(GDBFLAG) $(CPPFLAGS) $(CORE_INCLUDE) $(SPDLOG_INCLUDE) $(GLAD_INCLUDE) $(IMGUI_FRONTENDS_INCLUDE) $(IMGUI_BACKENDS_INCLUDE) $(GLM_INCLUDE) -o bin/intermidiate/SandboxApp $(sandbox_Srcs) -Lbin/lib $(CORE_FLAG) $(GLFW_FLAG) $(GLAD_FLAG) $(GL_FLAG) $(IMGUI_FLAG)

define build_CoreObjects
bin/objectFiles/core/$$(patsubst %.cpp,%.o,$$(notdir $(1))): $(1)
	g++ $$(GDBFLAG) $$(LIB_BUILD) $$(CPPFLAGS) $$(SPDLOG_INCLUDE) $$(GLAD_INCLUDE) $$(CORE_INCLUDE) $$(IMGUI_FRONTENDS_INCLUDE) $$(IMGUI_BACKENDS_INCLUDE) $$(GLM_INCLUDE) $$(TNC_DEBUG) -c $$< -o $$@
endef
$(foreach src,$(core_Srcs),$(eval $(call build_CoreObjects,$(src))))
