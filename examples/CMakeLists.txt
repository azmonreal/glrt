file(GLOB EXAMPLES_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(example_source ${EXAMPLES_SOURCES})
	get_filename_component(example_name ${example_source} NAME_WE)
	add_executable(${example_name} ${example_source})
	target_link_libraries(${example_name} ${PROJECT_NAME})
endforeach(example_source)

set(RESOURCES_DIR resources)
file(GLOB_RECURSE RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${RESOURCES_DIR}/*)

foreach(resource ${RESOURCES})
	configure_file(${resource} ${resource} COPYONLY)
endforeach()
