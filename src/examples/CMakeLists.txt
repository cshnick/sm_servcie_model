add_subdirectory(construct_destroy)
add_subdirectory(multy_component)
add_subdirectory(multy_object)
add_subdirectory(objects_as_params)
add_subdirectory(query_interface_1)
add_subdirectory(query_interface_2)
add_subdirectory(simple_component)
add_subdirectory(simple_enum)
add_subdirectory(simple_object)
add_subdirectory(string_enum)

add_custom_target(RegExamples
    COMMAND cp -v ${TOP_LEVEL}/bin/RegExamples.sh ${EXECUTABLE_OUTPUT_PATH}/RegExamples.sh
    DEPENDS ${TOP_LEVEL}/bin/RegExamples.sh
)