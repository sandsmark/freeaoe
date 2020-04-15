project(resgen)
add_executable(resgen main.cpp)

if(NOT MSVC)
    target_link_libraries(resgen stdc++fs)
endif()


function(add_resource generated_source)
    set(resource_file "${CMAKE_CURRENT_SOURCE_DIR}/${ARGV1}")
    set(outfile "${PROJECT_BINARY_DIR}/${ARGV1}")
    get_filename_component(filedir ${ARGV1} DIRECTORY)
    file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/${filedir}")
    add_custom_command(
        OUTPUT "${outfile}.c" "${outfile}.h"
        COMMAND resgen ${resource_file}
        DEPENDS resgen ${resource_file}
        WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/${filedir}"
        COMMENT "Generating code for resource ${resource_file}"
        VERBATIM
        )
    set(${generated_source} "${outfile}.c" PARENT_SCOPE)
endfunction()


