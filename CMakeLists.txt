cmake_minimum_required(VERSION 3.24)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    if(NOT DEFINED CMAKE_PROJECT_TOP_LEVEL_INCLUDES)
        set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES
            "${CMAKE_CURRENT_LIST_DIR}/cmake/dependencies.cmake"
        )
    endif()
endif()

project(example VERSION 0.0.1 LANGUAGES CXX)

add_library(example STATIC)

target_compile_features(example PUBLIC cxx_std_11)

file(GLOB_RECURSE EXAMPLE_PUBLIC_HEADERS CONFIGURE_DEPENDS include/*.hpp)
file(GLOB_RECURSE EXAMPLE_PRIVATE_HEADERS CONFIGURE_DEPENDS src/*.hpp)
file(GLOB_RECURSE EXAMPLE_SOURCES CONFIGURE_DEPENDS src/*.cpp)

target_sources(
    example
    PUBLIC
        FILE_SET example_public_headers
            TYPE HEADERS
            BASE_DIRS include
            FILES ${EXAMPLE_PUBLIC_HEADERS}
)

target_sources(
    example
    PRIVATE
        FILE_SET example_private_headers
            TYPE HEADERS
            BASE_DIRS src
            FILES ${EXAMPLE_PRIVATE_HEADERS}
)

target_sources(example PRIVATE ${EXAMPLE_SOURCES})

add_library(example::example ALIAS example)

option(EXAMPLE_BUILD_TESTING "build test" ${PROJECT_IS_TOP_LEVEL})
if(EXAMPLE_BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()

option(
    EXAMPLE_INSTALL
    "generate install rules for example"
    ${PROJECT_IS_TOP_LEVEL}
)

if(EXAMPLE_INSTALL)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)

    set(EXAMPLE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/example)

    install(
        TARGETS example
        EXPORT example-targets
        FILE_SET example_public_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(
        EXPORT example-targets
        FILE example-targets.cmake
        NAMESPACE example::
        DESTINATION ${EXAMPLE_INSTALL_CMAKEDIR}
    )

    configure_package_config_file(
        cmake/example-config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/example-config.cmake
        INSTALL_DESTINATION ${EXAMPLE_INSTALL_CMAKEDIR}
    )

    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/example-config-version.cmake
        COMPATIBILITY SameMajorVersion
    )

    install(
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/example-config.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/example-config-version.cmake
        DESTINATION ${EXAMPLE_INSTALL_CMAKEDIR}
    )
endif()
