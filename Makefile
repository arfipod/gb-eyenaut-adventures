PROJECT := terraria-gb-lite
ROM := build/$(PROJECT).gb
SOURCES := $(wildcard src/*.c)
INCLUDES := -Iinclude

GBDK_HOME ?= $(HOME)/opt/gbdk
RGBDS_HOME ?= $(HOME)/opt/rgbds

ifneq ($(wildcard $(GBDK_HOME)/bin/lcc),)
LCC ?= $(GBDK_HOME)/bin/lcc
PNG2ASSET ?= $(GBDK_HOME)/bin/png2asset
else
LCC ?= lcc
PNG2ASSET ?= png2asset
endif

ifneq ($(wildcard $(RGBDS_HOME)/rgbasm),)
RGBASM ?= $(RGBDS_HOME)/rgbasm
RGBLINK ?= $(RGBDS_HOME)/rgblink
RGBFIX ?= $(RGBDS_HOME)/rgbfix
RGBGFX ?= $(RGBDS_HOME)/rgbgfx
else
RGBASM ?= rgbasm
RGBLINK ?= rgblink
RGBFIX ?= rgbfix
RGBGFX ?= rgbgfx
endif

ifneq ($(wildcard $(HOME)/.local/bin/emulicious),)
EMULATOR ?= $(HOME)/.local/bin/emulicious
else
EMULATOR ?= emulicious
endif

PYBOY ?= $(HOME)/gbdev-sandbox/pyboy-venv/bin/pyboy

LCCFLAGS := $(INCLUDES) -Wm-yn"TERRARIA LITE"
EMULATOR_FLAGS ?= -scale 4
PYBOY_ENV ?= SDL_AUDIODRIVER=dummy LIBGL_ALWAYS_SOFTWARE=1 MESA_LOADER_DRIVER_OVERRIDE=llvmpipe

.PHONY: all clean run run-pyboy run-pyboy-x11 debug tools-check

all: $(ROM)

$(ROM): $(SOURCES) $(wildcard include/*.h) | build
	$(LCC) $(LCCFLAGS) -o $@ $(SOURCES)

build:
	mkdir -p build

clean:
	rm -f build/*.gb build/*.ihx build/*.noi build/*.map build/*.sym build/*.cdb build/*.adb
	rm -f src/*.asm src/*.lst src/*.o src/*.rel src/*.sym src/*.noi src/*.rst

run: $(ROM)
	@if ! command -v $(EMULATOR) >/dev/null 2>&1; then \
		echo "No emulator command found. Set EMULATOR=/path/to/emulator or install the emulicious launcher."; \
		exit 1; \
	fi
	@if [ "$(EMULATOR)" = "emulicious" ] && ! command -v java >/dev/null 2>&1; then \
		echo "Emulicious is installed, but Java is missing. Install it with: sudo apt install -y default-jre"; \
		exit 1; \
	fi
	$(EMULATOR) $(EMULATOR_FLAGS) $(ROM)

run-pyboy: $(ROM)
	@if [ ! -x "$(PYBOY)" ]; then \
		echo "PyBoy was not found at $(PYBOY)."; \
		echo "Create it with: python3 -m venv ~/gbdev-sandbox/pyboy-venv && ~/gbdev-sandbox/pyboy-venv/bin/python -m pip install pyboy"; \
		exit 1; \
	fi
	$(PYBOY_ENV) $(PYBOY) --window SDL2 --scale 4 --dmg --no-sound-emulation $(ROM)

run-pyboy-x11: $(ROM)
	@if [ ! -x "$(PYBOY)" ]; then \
		echo "PyBoy was not found at $(PYBOY)."; \
		echo "Create it with: python3 -m venv ~/gbdev-sandbox/pyboy-venv && ~/gbdev-sandbox/pyboy-venv/bin/python -m pip install pyboy"; \
		exit 1; \
	fi
	SDL_VIDEODRIVER=x11 $(PYBOY_ENV) $(PYBOY) --window SDL2 --scale 4 --dmg --no-sound-emulation $(ROM)

debug: run

tools-check:
	@echo "GBDK lcc:      $$(command -v $(LCC) || true)"
	@$(LCC) -v 2>&1 | head -n 1
	@echo "png2asset:     $$(command -v $(PNG2ASSET) || true)"
	@$(PNG2ASSET) --help >/dev/null 2>&1 && echo "png2asset:     ok" || echo "png2asset:     present, help check skipped"
	@echo "RGBDS rgbasm:  $$(command -v $(RGBASM) || true)"
	@$(RGBASM) --version
	@echo "RGBDS rgblink: $$(command -v $(RGBLINK) || true)"
	@$(RGBLINK) --version
	@echo "RGBDS rgbfix:  $$(command -v $(RGBFIX) || true)"
	@$(RGBFIX) --version
	@echo "RGBDS rgbgfx:  $$(command -v $(RGBGFX) || true)"
	@$(RGBGFX) --version
	@echo "Emulator:      $$(command -v $(EMULATOR) || true)"
	@echo "PyBoy:         $(PYBOY)"
	@if command -v java >/dev/null 2>&1; then java -version 2>&1 | head -n 1; else echo "Java:          missing"; fi
