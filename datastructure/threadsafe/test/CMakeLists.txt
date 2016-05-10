cmake_minimum_required( VERSION 2.8.3 )

if ( NOT DEFINED COMMON_DATASTRUCTURE_THREADSAFE_TEST_CMAKE )
    set ( COMMON_DATASTRUCTURE_THREADSAFE_TEST_CMAKE 1 )

    message("Configuring common data structure thread-safe test")

    project ( COMMON_DATASTRUCTURE_THREADSAFE )

    # Include the global locations file
    include ( ${CMAKE_CURRENT_LIST_DIR}/../../../../build/CMakePaths.txt )

    # Include the list of source files here
    include ( ${COMMON_DATASTRUCTURE_THREADSAFE_TEST_DIR}/CMakeSources.txt )

    include ( ${COMMON_DATASTRUCTURE_THREADSAFE_DIR}/CMakeLists.txt )

    # Add external library
    link_directories ( ${COMMON_DATASTRUCTURE_THREADSAFE_TEST_DIR};
                       ${LOG4CXX_LIB_DIR};
                       ${A7C_UNIT_TEST_LIB_DIR};
                     )

    # Creates executable
    set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${COMMON_DATASTRUCTURE_THREADSAFE_TEST_DIR}" )
    add_executable ( CCommonDataStructureThreadSafeTestSuite ${COMMON_DATA_STRUCTURE_THREAD_SAFE_TEST_SOURCES} ${COMMON_DATA_STRUCTURE_THREAD_SAFE_TEST_MAIN_SOURCES} )

    # Executable Dependencies
    # add_dependencies ( CCommonDataStructureThreadSafeTestSuite)

    target_link_libraries ( CCommonDataStructureThreadSafeTestSuite log4cxx apr-1 aprutil-1 a7ctestlib_ix86_64-linux-sles11 )

endif()

