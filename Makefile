# -----------------------------------------------------------------------------
#     ____  __  ______   ___   ____ ___  ___
#    / __ \/ / /_  __/  |__ \ / __ \__ \<  /
#   / /_/ / /   / /     __/ // / / /_/ // / 
#  / ____/ /___/ /     / __// /_/ / __// /  
# /_/   /_____/_/     /____/\____/____/_/ 
# 
# -----------------------------------------------------------------------------    

# make sure filename does not contains space !
HEADERS:=$(shell find src -type f -name '*.h')

# clean everything, reconfig everything, recompile everything
all: | clean extern configure build 

# -----------------------------------------------------------------------------
# clean
# -----------------------------------------------------------------------------

# clean compiled files and generated header
clean:
	@echo [DEBUG] Root Makefile : clean
	@rm -rf bin build
	@rm -f $(shell grep -ls '// Generated by dia2code' main.h ${HEADERS})

# removes everything that is generated, including external dependencies
# make -s : Silent operation
# Change to directory dir before reading the makefiles or doing anything else
distclean: clean
	@echo [DEBUG] Root Makefile : distclean
	@$(MAKE) -s -C extern clean

# -----------------------------------------------------------------------------
# external
# -----------------------------------------------------------------------------

# configure and compile external dependency
extern: bin/dia2code
	@echo [DEBUG] Root Makefile : extern

bin/dia2code:
	@$(MAKE) -s -j4 -C extern dia2code

# configure the project
configure:
	@echo [DEBUG] Root Makefile : configure
	@mkdir -p build
	@cd build && cmake ..

# -----------------------------------------------------------------------------
# build 
# -----------------------------------------------------------------------------

# compile all exe (client, server, ...)
#
build:
	@echo [DEBUG] Root Makefile : build
	@cd build && make

bin/client:
	@$(MAKE) -s -j4 -C build client

bin/server:
	@$(MAKE) -s -j4 -C build server

# -----------------------------------------------------------------------------
# docker 
# -----------------------------------------------------------------------------
test:
	docker build -t plt-initial -f docker/plt-initial .
	./docker/validate.sh plt-test
	./docker/run_docker_bash.sh plt-test

# -----------------------------------------------------------------------------
# pdf from dia
# -----------------------------------------------------------------------------

diapdf: rapport/state.pdf rapport/render.pdf rapport/engine.pdf rapport/ai.pdf rapport/module.pdf

rapport/state.pdf: src/state.dia
	dia -e rapport/state.ps $<
	ps2pdf rapport/state.ps $@
	rm -f rapport/state.ps

rapport/render.pdf: src/render.dia
	dia -e rapport/render.ps $<
	ps2pdf rapport/render.ps $@
	rm -f rapport/render.ps

rapport/engine.pdf: src/engine.dia
	dia -e rapport/engine.ps $<
	ps2pdf rapport/engine.ps $@
	rm -f rapport/engine.ps

rapport/ai.pdf: src/ai.dia
	dia -e rapport/ai.ps $<
	ps2pdf rapport/ai.ps $@
	rm -f rapport/ai.ps

rapport/module.pdf: src/module.dia
	dia -e rapport/module.ps $<
	ps2pdf rapport/module.ps $@
	rm -f rapport/module.ps

# -----------------------------------------------------------------------------
# pdf from dia
# -----------------------------------------------------------------------------

list:
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$'

.PHONY: configure build clean extern test list
