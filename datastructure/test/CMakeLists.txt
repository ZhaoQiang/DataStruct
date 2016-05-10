cmake_minimum_required( VERSION 2.8.3 )

if ( NOT DEFINED COMMON_DATASTRUCTURE_TEST_CMAKE )
    set ( COMMON_DATASTRUCTURE_TEST_CMAKE 1 )

    message("Configuring common datastructure test")

    project ( COMMON_DATASTRUCTURE_TEST )

    # Include the global locations file
    include ( ${CMAKE_CURRENT_LIST_DIR}/../../../build/CMakePaths.txt )

    # Include the list of source files here
    include ( ${COMMON_DATASTRUCTURE_TEST_DIR}/CMakeSources.txt )

    include ( ${COMMON_DATASTRUCTURE_DIR}/CMakeLists.txt )

    # Add external library
    link_directories ( ${COMMON_DATASTRUCTURE_DIR};
                       ${A7C_UNIT_TEST_LIB_DIR};
                     )

    # Creates executable
    set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" )
    add_executable ( CCommonDataStructureTestSuite ${COMMON_DATASTRUCTURE_TEST_SOURCES} ${COMMON_DATASTRUCTURE_TEST_MAIN_SOURCES})

    # Executable Dependencies
    add_dependencies ( CCommonDataStructureTestSuite 
        CommonDataStructure; )

    target_link_libraries ( CCommonDataStructureTestSuite CommonDataStructure a7ctestlib_ix86_64-linux-sles11)

endif()

