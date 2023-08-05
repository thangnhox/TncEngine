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
GL_FLAG = -lGL
IMGUI_FLAG = -limgui

# Third party include
SPDLOG_INCLUDE = -Icore/vendore/spdlog/include
GLFW_INCLUDE = -Icore/vendore/GLFW/include
GLAD_INCLUDE = -Icore/vendore/Glad/include
IMGUI_FRONTENDS_INCLUDE = -Icore/vendore/ImGUI/frontends
IMGUI_BACKENDS_INCLUDE = -Icore/vendore/ImGUI/backends
GLM_INCLUDE = -Icore/vendore/glm

# My include
CORE_INCLUDE = -Icore/src

.PHONY: core sandbox setup core_PCH test

# Makefile Variable
SHELL = /bin/bash

core_Srcs = $(shell find core/src/ -name '*.cpp')
core_Objs = $(foreach file,$(patsubst %.cpp,%.o,$(notdir $(core_Srcs))),bin/objectFiles/core/$(file))
core_Include = $(foreach file,$(patsubst %.cpp,%.include,$(notdir $(core_Srcs))),bin/includeList/core/$(file))
core_Lib = bin/lib/libTncEngineCore.a
glad_Srcs = $(shell find core/vendore/Glad/ -name '*.c')
glad_Objs = $(foreach file,$(patsubst %.c,%.o,$(notdir $(glad_Srcs))),bin/objectFiles/glad/$(file))
glad_Lib = bin/lib/libglad.a
imgui_Srcs = $(shell find core/vendore/ImGUI/ -name '*.cpp')
imgui_Objs = $(foreach file,$(patsubst %.cpp,%.o,$(notdir $(imgui_Srcs))),bin/objectFiles/imgui/$(file))
imgui_Lib = bin/lib/libimgui.a

sandbox_Srcs = $(shell find sandbox/src/ -name '*.cpp')
sandbox_Exe = bin/intermidiate/SandboxApp

glfw3_Lib = bin/lib/libglfw3.a
binary_Folders = bin/intermidiate bin/submoduleBuild/GLFW bin/objectFiles/core bin/objectFiles/glad bin/objectFiles/imgui bin/lib bin/includeList/core

# Make some empty object files in case find could not detect files in first compile
setup: $(binary_Folders) $(glfw3_Lib) $(glad_Lib) $(imgui_Lib)
	@echo setup done

$(binary_Folders):
	mkdir -p $@

$(glfw3_Lib):
	cmake -S core/vendore/GLFW -B bin/submoduleBuild/GLFW
	cd bin/submoduleBuild/GLFW && $(MAKE) && cp src/libglfw3.a ../../lib/

core: $(binary_Folders) $(core_Lib)
	@echo done

core_PCH:
	g++ $(CPPFLAGS) $(SPDLOG_INCLUDE) $(CORE_INCLUDE) core/src/TncPCH.hpp

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
	g++ $(GDBFLAG) $(CPPFLAGS) -Lbin/lib $(CORE_INCLUDE) $(SPDLOG_INCLUDE) $(GLAD_INCLUDE) $(IMGUI_FRONTENDS_INCLUDE) $(IMGUI_BACKENDS_INCLUDE) $(GLM_INCLUDE) -o $@ $(sandbox_Srcs) $(CORE_FLAG) $(GLFW_FLAG) $(GLAD_FLAG) $(GL_FLAG) $(IMGUI_FLAG)

define build_CoreObjects
bin/objectFiles/core/$$(patsubst %.cpp,%.o,$$(notdir $(1))): $(1) $(filter-out $(1),$(shell cat bin/includeList/core/$(patsubst %.cpp,%.include,$(notdir $(1))) 2>/dev/null))
	g++ $$(GDBFLAG) $$(LIB_BUILD) $$(CPPFLAGS) $$(SPDLOG_INCLUDE) $$(GLAD_INCLUDE) $$(CORE_INCLUDE) $$(IMGUI_FRONTENDS_INCLUDE) $$(IMGUI_BACKENDS_INCLUDE) $$(GLM_INCLUDE) $$(TNC_DEBUG) -c $$< -o $$@
endef

# Generate user header list for specific Source file include every header inside vendore will update if source is modified
# My opinion is if header is modified any source related to it need to be recompile
define gen_CoreIncludeList
bin/includeList/core/$$(patsubst %.cpp,%.include,$$(notdir $(1))): $(1) bin/objectFiles/core/$(patsubst %.cpp,%.o,$(notdir $(1)))
	g++ -MM $$(SPDLOG_INCLUDE) $$(GLAD_INCLUDE) $$(CORE_INCLUDE) $$(IMGUI_FRONTENDS_INCLUDE) $$(IMGUI_BACKENDS_INCLUDE) $$(GLM_INCLUDE) $(1) > $$(patsubst %.include,%.tmp,$$@)
	cat $$(patsubst %.include,%.tmp,$$@) | sed 's/$$(patsubst %.cpp,%.o,$$(notdir $(1))): //g' | sed 's/\\//g' - > $$@
	rm $$(patsubst %.include,%.tmp,$$@)
endef

$(core_Lib) : $(core_Include) $(core_Objs)
	ar src $@ $(core_Objs)

test: $(shell cat bin/includeList/core/Layer.include)
	echo $^

$(foreach src,$(core_Srcs),$(eval $(call gen_CoreIncludeList,$(src))))
$(foreach src,$(core_Srcs),$(eval $(call build_CoreObjects,$(src))))
