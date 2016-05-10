cmake_minimum_required( VERSION 2.8.3 )

if ( NOT DEFINED COMMON_DATASTRUCTURE_THREADSAFE_CMAKE )
    set ( COMMON_DATASTRUCTURE_THREADSAFE_CMAKE 1 )

    message("Configuring common datastructure threadsafe")

    project ( COMMON_DATASTRUCTURE_THREADSAFE )

    # Include the global locations file
    include ( ${CMAKE_CURRENT_LIST_DIR}/../../../build/CMakePaths.txt )

    # Include the list of source files here
    include ( ${COMMON_DATASTRUCTURE_THREADSAFE_DIR}/CMakeSources.txt )

    #Creates shared libraries
    set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${COMMON_DATASTRUCTURE_THREADSAFE_DIR}" )
#    add_library ( CommonDataStructureThreadSafe SHARED ${COMMON_THREADSAFE_SOURCES} )

#    target_link_libraries ( CommonDataStructureThreadSafe )

endif()

