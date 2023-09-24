export UID_VALUE=$(shell id -u)
export GID_VALUE=$(shell id -g)

BUILD_TYPES := Debug Release luasan tsan

USE_DOCKER ?= $(shell ./tools/not_running_in_docker)
DOCKER_CMD = docker-compose run --rm dev bash
ifeq ($(USE_DOCKER),1)
    define run_in_container
        $(DOCKER_CMD) -c '$(1)'
    endef
else
    define run_in_container
        $(1)
    endef
endif

# Function to return the nth word in a sequence of words separated by the '.'
# character.
# $1 : string of '.' Separated words
# $2 : the number of the word you'd like returned where 1 is the first word.
# Usage Example:
# $(call word_dot,foo.bar.baz,1) = foo
# $(call word_dot,foo.bar.baz,2) = bar
# $(call word_dot,foo.bar.baz,3) = baz
# $(call word_dot,foo,1) = foo
word_dot = $(word $2,$(subst ., ,$1))


COMPILERS = \
    gcc \
    clang \

.PHONY: all
all: $(addprefix test., $(COMPILERS))

# By default, GNU make removes intermediate files. Since all CMake targets
# depend on build/%/CMakeCache.txt Make sometimes wants to delete it. To prevent
# that behavior it is marked as precious with .PRECIOUS. I thought making it an
# order-only-prerequisite would prevent it from being removed, but for whatever
# reason that doesn't always seem to be the case.
.PRECIOUS: build/%/CMakeCache.txt
build/%/CMakeCache.txt:
	$(call run_in_container, \
		cmake --preset $(call word_dot,$*,1); \
		cmake -E create_symlink build/$(call word_dot,$*,1)/compile_commands.json compile_commands.json; \
	)

# build/%/CMakeCache.txt following the pipe makes it a special perquisite
# called an order-only-prerequisites. Order-only-prerequisite will be built before
# a target like an normal prerequisite, but without forcing the target to be
# updated if the prerequisite is updated. This is desirable in this case the
# CMake config step should only be explicitly done once and every subsequent
# time, will be done implicitly by running the build system generated by the
# CMake config step.
build.%: | build/%/CMakeCache.txt
	@if [ "$(words $(subst ., ,$*))" = 1 ]; then \
		$(call run_in_container, \
			CTEST_OUTPUT_ON_FAILURE=1 \
			cmake --build --preset $* \
		); \
	else \
		$(call run_in_container, \
			CTEST_OUTPUT_ON_FAILURE=1 \
			cmake --build --preset $(call word_dot,$*,1) --target $(call word_dot,$*,2) \
		); \
	fi

.SECONDEXPANSION:
test.%: $(addprefix build., $$*)
	@if [ "$(words $(subst ., ,$*))" = 1 ]; then \
		$(call run_in_container, \
			CTEST_OUTPUT_ON_FAILURE=1 \
			ctest -V --preset $* \
		); \
	else \
		$(call run_in_container, \
			CTEST_OUTPUT_ON_FAILURE=1 \
			ctest -V --preset $(call word_dot,$*,1) --tests-regex $(call word_dot,$*,2) \
		); \
	fi

.PHONY: nuke
nuke:
	rm -rf ./build

.PHONY: shell
shell:
	$(DOCKER_CMD)

.PHONY: docker-down
docker-down:
	docker-compose down

.PHONY: docker-build
docker-build:
	docker-compose build
