.PHONY: core sandbox

core:
	g++ -Wall -shared -std=c++17 -g -fPIC -c $(shell find core/src/ -name '*.cpp')
	mv *.o bin/objectFiles/core/
	ar src bin/lib/libTncEngineCore.a $(shell find bin/objectFiles/core/ -name '*.o')

sandbox:
	g++ -Lbin/lib -Icore/src -o bin/intermidiate/SanboxApp $(shell find sandbox/src/ -name '*.cpp') -lTncEngineCore