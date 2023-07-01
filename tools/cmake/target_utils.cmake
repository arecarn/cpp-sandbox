################################################################################
# Recursively find all targets
################################################################################
function(get_all_targets _result _dir)
    get_property(subdirs DIRECTORY "${_dir}" PROPERTY SUBDIRECTORIES)
    foreach(subdir IN LISTS subdirs)
        get_all_targets(${_result} "${subdir}")
    endforeach()
    get_directory_property(sub_targets DIRECTORY "${_dir}" BUILDSYSTEM_TARGETS)
    set(${_result} ${${_result}} ${sub_targets} PARENT_SCOPE)
endfunction()
