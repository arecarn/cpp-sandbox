################################################################################
# CMake Modules Includes
################################################################################
include(cppcheck)
include(clang_tidy)

################################################################################
# Subdirectories
################################################################################
add_subdirectory(array)
add_subdirectory(pong)
add_subdirectory(ringbuffer)
add_subdirectory(span)
add_subdirectory(chsm)
add_subdirectory(tagged_union)
add_subdirectory(pod_variant)
add_subdirectory(yahsm)
add_subdirectory(questions)
