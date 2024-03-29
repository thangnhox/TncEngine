VULKAN_FLAG = -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
CPPFLAGS = -std=c++17 -Wall
CFLAGS = -std=c17 -Wall
LIB_BUILD = -shared -fPIC
GDBFLAG = -g

DEFINE = -D TNC_PROFILE
ENABLE_ASSERT = -D ENABLE_ASSERT
GLFW_INCLUDE_NONE = -D GLFW_INCLUDE_NONE
TNC_DEBUG = -D TNC_DEBUG

# Libraries
GLFW_FLAG = -lglfw3
GLAD_FLAG = -lglad
CORE_FLAG = -lTncEngineCore
GL_FLAG = -lGL
IMGUI_FLAG = -limgui

# Third party include
SPDLOG_INCLUDE = -ITncEngine/vendore/spdlog/include
GLFW_INCLUDE = -ITncEngine/vendore/GLFW/include
GLAD_INCLUDE = -ITncEngine/vendore/Glad/include
IMGUI_FRONTENDS_INCLUDE = -ITncEngine/vendore/ImGUI/frontends
IMGUI_BACKENDS_INCLUDE = -ITncEngine/vendore/ImGUI/backends
GLM_INCLUDE = -ITncEngine/vendore/glm
STB_INCLUDE = -ITncEngine/vendore/stb_image

# My include
CORE_INCLUDE = -ITncEngine/src

.PHONY: core sandbox setup core_PCH test

# Makefile Variable
SHELL = /bin/bash

core_Srcs = $(shell find TncEngine/src/ -name '*.cpp') TncEngine/vendore/stb_image/stb_image.cpp
core_Objs = $(foreach file,$(patsubst %.cpp,%.o,$(notdir $(core_Srcs))),bin/objectFiles/TncEngine/$(file))
core_Include = $(foreach file,$(patsubst %.cpp,%.include,$(notdir $(core_Srcs))),bin/includeList/TncEngine/$(file))
core_Lib = bin/lib/libTncEngineCore.a
glad_Srcs = $(shell find TncEngine/vendore/Glad/ -name '*.c')
glad_Objs = $(foreach file,$(patsubst %.c,%.o,$(notdir $(glad_Srcs))),bin/objectFiles/glad/$(file))
glad_Lib = bin/lib/libglad.a
imgui_Srcs = $(shell find TncEngine/vendore/ImGUI/ -name '*.cpp')
imgui_Objs = $(foreach file,$(patsubst %.cpp,%.o,$(notdir $(imgui_Srcs))),bin/objectFiles/imgui/$(file))
imgui_Lib = bin/lib/libimgui.a

sandbox_Srcs = $(shell find sandbox/src/ -name '*.cpp')
sandbox_Exe = bin/intermidiate/SandboxApp

glfw3_Lib = bin/lib/libglfw3.a
binary_Folders = bin/intermidiate bin/submoduleBuild/GLFW bin/objectFiles/TncEngine bin/objectFiles/glad bin/objectFiles/imgui bin/lib bin/includeList/TncEngine bin/Profiler

# Make some empty object files in case find could not detect files in first compile
setup: $(binary_Folders) $(glfw3_Lib) $(glad_Lib) $(imgui_Lib)
	@echo setup done

$(binary_Folders):
	mkdir -p $@

$(glfw3_Lib):
	cmake -S TncEngine/vendore/GLFW -B bin/submoduleBuild/GLFW
	cd bin/submoduleBuild/GLFW && $(MAKE) && cp src/libglfw3.a ../../lib/

core: $(binary_Folders) $(core_Lib)
	@echo done

core_PCH:
	g++ $(CPPFLAGS) $(SPDLOG_INCLUDE) $(CORE_INCLUDE) TncEngine/src/TncPCH.hpp

sandbox: $(binary_Folders) $(sandbox_Exe)
	gdb $(sandbox_Exe)

$(glad_Lib):
	@$(foreach file,$(glad_Srcs),\
	echo "Compiling $(file)";\
	gcc $(GDBFLAG) $(CFLAGS) $(LIB_BUILD) $(GLAD_INCLUDE) -c $(file) -o bin/objectFiles/glad/$(patsubst %.c,%.o,$(notdir $(file)));)
	ar src $@ $(glad_Objs)

$(imgui_Lib):
	@$(foreach file,$(imgui_Srcs),\
	echo "Compiling $(file)";\
	g++ $(GDBFLAG) $(CPPFLAGS) $(LIB_BUILD) $(IMGUI_FRONTENDS_INCLUDE) $(IMGUI_BACKENDS_INCLUDE) -c $(file) -o bin/objectFiles/imgui/$(patsubst %.cpp,%.o,$(notdir $(file)));)
	ar src $@ $(imgui_Objs)

$(sandbox_Exe): $(glfw3_Lib) $(glad_Lib) $(imgui_Lib) $(core_Lib) $(sandbox_Srcs)
	$(info Compiling $@)
	@g++ $(GDBFLAG) $(CPPFLAGS) -Lbin/lib $(CORE_INCLUDE) $(GLFW_INCLUDE) $(SPDLOG_INCLUDE) $(GLAD_INCLUDE) $(IMGUI_FRONTENDS_INCLUDE) $(IMGUI_BACKENDS_INCLUDE) $(GLM_INCLUDE) $(STB_INCLUDE) -o $@ $(sandbox_Srcs) $(CORE_FLAG) $(GLFW_FLAG) $(GLAD_FLAG) $(GL_FLAG) $(IMGUI_FLAG) $(DEFINE)

define build_CoreObjects
bin/objectFiles/TncEngine/$$(patsubst %.cpp,%.o,$$(notdir $(1))): $(1) $(filter-out $(1),$(shell cat bin/includeList/TncEngine/$(patsubst %.cpp,%.include,$(notdir $(1))) 2>/dev/null))
	$$(info Compiling $(1))
	@g++ $$(GDBFLAG) $$(LIB_BUILD) $$(CPPFLAGS) $$(GLFW_INCLUDE) $$(SPDLOG_INCLUDE) $$(GLAD_INCLUDE) $$(CORE_INCLUDE) $$(IMGUI_FRONTENDS_INCLUDE) $$(IMGUI_BACKENDS_INCLUDE) $$(GLM_INCLUDE) $$(STB_INCLUDE) $$(TNC_DEBUG) -c $$< -o $$@
endef

# Generate user header list for specific Source file include every header inside vendore will update if source is modified
# My opinion is if header is modified any source related to it need to be recompile
define gen_CoreIncludeList
bin/includeList/TncEngine/$$(patsubst %.cpp,%.include,$$(notdir $(1))): $(1) bin/objectFiles/TncEngine/$(patsubst %.cpp,%.o,$(notdir $(1)))
	$$(info Generating $$@)
	@g++ -MM $$(SPDLOG_INCLUDE) $$(GLAD_INCLUDE) $$(CORE_INCLUDE) $$(IMGUI_FRONTENDS_INCLUDE) $$(IMGUI_BACKENDS_INCLUDE) $$(GLM_INCLUDE) $$(STB_INCLUDE) $(1) > $$(patsubst %.include,%.tmp,$$@)
	@cat $$(patsubst %.include,%.tmp,$$@) | sed 's/$$(patsubst %.cpp,%.o,$$(notdir $(1))): //g' | sed 's/\\//g' - > $$@
	@rm $$(patsubst %.include,%.tmp,$$@)
endef

$(core_Lib) : $(core_Include) $(core_Objs)
	$(info Generating $@)
	@ar src $@ $(core_Objs)

$(foreach src,$(core_Srcs),$(eval $(call gen_CoreIncludeList,$(src))))
$(foreach src,$(core_Srcs),$(eval $(call build_CoreObjects,$(src))))
