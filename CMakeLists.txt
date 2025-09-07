cmake_minimum_required(VERSION 3.16)
project(TenshiEngine VERSION 0.4.0 LANGUAGES CXX)

file(GLOB_RECURSE TENSHIENGINE_SRC CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(TenshiEngine STATIC ${TENSHIENGINE_SRC})

target_include_directories(TenshiEngine 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR} 
)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

target_link_libraries(TenshiEngine PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS TenshiEngine EXPORT TenshiEngineTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT TenshiEngineTargets
    FILE TenshiEngineTargets.cmake
    NAMESPACE te::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TenshiEngine)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/TenshiEngineConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/TenshiEngineConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/TenshiEngineConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TenshiEngine
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/TenshiEngineConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/TenshiEngineConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TenshiEngine
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/TenshiEngine/version.h
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
    @ONLY
)

add_custom_target(uninstall
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)
