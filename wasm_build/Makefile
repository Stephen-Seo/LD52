ifdef RELEASE
	OTHER_FLAGS = -DNDEBUG -O3
else
	OTHER_FLAGS = -O0
endif

SOURCES = \
		../src/main.cc \
		../src/ems.cc \
		../src/game.cc \
		../src/constants.cc \
		../src/helpers.cc

HEADERS = \
		../src/constants.h \
		../src/game.h \
		../src/ems.h \
		../src/helpers.h

CXX = source ${HOME}/git/emsdk/emsdk_env.sh && em++

all: | format ld52_harvest_cut.html index.html

ld52_harvest_cut.html: ${SOURCES} ${HEADERS}
	${CXX} -o ld52_harvest_cut.html \
		-s USE_GLFW=3 -I../wasm_includes -L../wasm_libs -lraylib \
		--shell-file custom_shell.html \
		-sEXPORTED_FUNCTIONS=_main \
		-sEXPORTED_RUNTIME_METHODS=ccall \
		--preload-file ../resources \
		${OTHER_FLAGS} \
		${SOURCES}

.PHONY: clean format index.html

index.html:
	ln -sf ld52_harvest_cut.html index.html

clean:
	rm -f ld52_harvest_cut.html
	rm -f ld52_harvest_cut.js
	rm -f ld52_harvest_cut.wasm
	rm -f ld52_harvest_cut.data
	rm -f index.html

format:
	clang-format -i --style=file ${SOURCES} ${HEADERS}
