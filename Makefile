CC = clang
LD = $(shell brew --prefix llvm)/bin/clang
CCFLAGS =
LDFLAGS =

OUTDIR=bin
SRCDIR=src

PATH_LIB = lib
PATH_SDL = $(PATH_LIB)/SDL

DYLIB = dylib
DEFINES_NATIVE = -DPLATFORM_OSX

INCFLAGS  = -iquotesrc
INCFLAGS += -I$(PATH_SDL)/include

EMCCFLAGS += -std=gnu2x
EMCCFLAGS += -Wall
EMCCFLAGS += -Wextra
EMCCFLAGS += -Wpedantic
EMCCFLAGS += -Wno-unused-parameter
EMCCFLAGS += -Wno-gnu
EMCCFLAGS += -pthread
EMCCLFAGS += -s INITIAL_MEMORY=256MB
EMCCLFAGS += -s TOTAL_MEMORY=256MB
EMCCFLAGS += --preload-file res
EMCCFLAGS += -s USE_SDL=2
EMCCFLAGS += -s FULL_ES3

CCFLAGS += -std=gnu2x
CCFLAGS += -O2
CCFLAGS += -Wall
CCFLAGS += -Wextra
CCFLAGS += -Wpedantic
CCFLAGS += -Wno-unused-parameter
CCFLAGS += -Wno-gnu
CCFLAGS += -Wno-fixed-enum-extension
CCFLAGS += -I/opt/homebrew/include -L/opt/homebrew/opt/llvm/lib -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lm
CXXFLAGS= $(CCFLAGS)

CCFLAGS += $(shell sdl2-config --cflags)
LDFLAGS += $(shell sdl2-config --libs)
LDFLAGS += -lstdc++
LDFLAGS_STATIC = $(LDFLAGS)
LDFLAGS_STATIC += $(shell $(BIN)/sdl/sdl2-config --prefix=$(BIN) --static-libs)

LDFLAGS_SHARED = $(LDFLAGS)
LDFLAGS_SHARED += -Lbin/lib
LDFLAGS_SHARED += -lSDL2-2.0
LDFLAGS_SHARED += -Wl,-rpath -Wl,bin/lib

C_SRCS = $(wildcard src/*.c)
C_OBJS = $(C_SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.o)

.PHONY: all build dir clean

all: build

$(BIN):
	$(shell mkdir -p $@)

dirs: $(BIN) FORCE
	$(shell mkdir -p $(BIN))
	$(shell mkdir -p $(BIN)/src)
	$(shell mkdir -p $(BIN)/util)
	rsync -a --include '*/' --exclude '*' "src" "bin"

build: ./$(C_OBJS)

lib-sdl: $(BIN)
	$(shell mkdir -p $(BIN)/sdl)
	$(shell mkdir -p $(BIN)/lib)
	cmake -S $(PATH_SDL) -B $(BIN)/sdl
	cd $(BIN)/sdl && make -j 10
	chmod +x $(BIN)/sdl/sdl2-config
	cp $(BIN)/sdl/libSDL2-2.0.$(DYLIB) $(BIN)/lib
	cp $(BIN)/lib/libSDL2-2.0.$(DYLIB) $(BIN)/lib/libSDL2.$(DYLIB)
	cp $(BIN)/lib/libSDL2-2.0.$(DYLIB) $(BIN)/lib/libSDL2-2.0.0.$(DYLIB)
	cp $(BIN)/sdl/libSDL2.a $(BIN)/lib

$(BIN): ./$(C_OBJS)

$(C_OBJS): $(OUTDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) $(INCFLAGS) $(DEFINES_NATIVE) $< -o $@

dir:
	@mkdir -p $(OUTDIR)
	@mkdir -p $(SRCDIR)


clean:
	rm -f *.o
	rm -f $(OUTDIR)/*
