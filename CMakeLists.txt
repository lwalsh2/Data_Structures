project(
    Data_Structures
    LANGUAGES "C"
    DESCRIPTION "C-based data structures project"
)

if (DEBUG EQUAL "1")
    message("DEBUGGING VERSION")
    add_compile_definitions(DEBUG)
else()
    message("RELEASE VERSION")
endif()

add_subdirectory(src)
