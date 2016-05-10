cmake_minimum_required( VERSION 2.8.3 )

if ( NOT DEFINED COMMON_DATASTRUCTURE_CMAKE )
    set ( COMMON_DATASTRUCTURE_CMAKE 1 )

    project ( COMMON_DATASTRUCTURE )


    # Include the global locations file
    include ( ${CMAKE_CURRENT_LIST_DIR}/../../build/CMakePaths.txt )

    # Include the list of source files here
    include ( ${COMMON_DATASTRUCTURE_DIR}/CMakeSources.txt )

    # Add external library

    link_directories (
                     )

    #Creates shared libraries
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" )
    add_library ( CommonDataStructure SHARED ${COMMON_DATASTRUCTURE_SOURCES} )

    target_link_libraries ( CommonDataStructure )

endif()

