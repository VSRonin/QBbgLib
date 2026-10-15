cmake_minimum_required(VERSION 3.20)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
message(STATUS "Found Qt Core ${Qt${QT_VERSION_MAJOR}Core_VERSION}")
if(NOT QBBGLIB_OFFLINE)
    find_package(Blpapi)
    if(NOT Blpapi_FOUND)
        set(QBBGLIB_OFFLINE ON)
        message(WARNING "Could Not Find Bloomberg API, reverting to offline mode")
    endif()
endif()

if(BUILD_DOCS)
    find_package(Doxygen OPTIONAL_COMPONENTS mscgen dia dot)
    if(DOXYGEN_FOUND)
        message(STATUS "Found Doxygen ${DOXYGEN_VERSION}")
    else()
        set(BUILD_DOCS OFF)
    endif()
endif()

set(qbbglib_HEADERS 
    QBbgSecurity.h 
    QBbgManager.h 
    QBbgOverride.h 
    QBbgRequestGroup.h 
    QBbgAbstractFieldRequest.h 
    QBbgAbstractRequest.h 
    QBbgHistoricalDataRequest.h 
    QBbgPortfolioDataRequest.h 
    QBbgAbstractIntradayRequest.h 
    QbbgReferenceDataRequest.h 
    QBbgAbstractFieldResponse.h 
    QBbgAbstractResponse.h 
    QBbgHistoricalDataResponse.h 
    QBbgPortfolioDataResponse.h 
    QBbgReferenceDataResponse.h 
    QBbgIntradayTickRequest.h
    QBbgAbstractIntradayResponse.h 
    QBbgIntradayTickResponse.h
)
set(qbbglib_PRIVATE_HEADERS 
    private/QBbgAbstractFieldRequest_p.h 
    private/QBbgAbstractFieldResponse_p.h 
    private/QBbgAbstractIntradayRequest_p.h 
    private/QBbgAbstractRequest_p.h 
    private/QBbgAbstractResponse_p.h 
    private/QBbgHistoricalDataRequest_p.h 
    private/QBbgHistoricalDataResponse_p.h 
    private/QBbgManager_p.h 
    private/QBbgOverride_p.h 
    private/QBbgPortfolioDataRequest_p.h 
    private/QBbgPortfolioDataResponse_p.h 
    private/QBbgReferenceDataRequest_p.h 
    private/QBbgReferenceDataResponse_p.h 
    private/QBbgRequestGroup_p.h 
    private/QBbgSecurity_p.h 
    private/QBbgAbstractWorker_p.h 
    private/QBbgRequestResponseWorker_p.h 
    private/QBbgIntradayTickRequest_p.h 
    private/QBbgAbstractIntradayResponse_p.h 
    private/QBbgIntradayTickResponse_p.h
    private/QBbgSessionMonitorWorker_p.h
)
set(qbbglib_SRCS
    QBbgManager.cpp 
    QBbgOverride.cpp 
    QBbgSecurity.cpp 
    QBbgAbstractRequest.cpp 
    QBbgHistoricalDataRequest.cpp 
    QBbgAbstractIntradayRequest.cpp 
    QBbgPortfolioDataRequest.cpp 
    QBbgReferenceDataRequest.cpp 
    QBbgRequestGroup.cpp 
    QBbgAbstractFieldRequest.cpp 
    QBbgAbstractFieldResponse.cpp 
    QBbgAbstractResponse.cpp 
    QBbgHistoricalDataResponse.cpp 
    QBbgPortfolioDataResponse.cpp 
    QBbgReferenceDataResponse.cpp 
    QBbgAbstractWorker.cpp
    QBbgRequestResponseWorker.cpp
    QBbgIntradayTickRequest.cpp 
    QBbgAbstractIntradayResponse.cpp 
    QBbgIntradayTickResponse.cpp
    QBbgSessionMonitorWorker.cpp
)

if(BUILD_DOCS)
    set(htmlDocRedirect "<!DOCTYPE html><html><head><title>Redirect</title><meta http-equiv=\"refresh\" content=\"0; url=html/index.html\" /></head><body><p><a href=\"html/index.html\">Click here if you are not redirected automatically</a></p></body></html>")
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/docs/htmldocs.html" ${htmlDocRedirect})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../docs/DoxygenConfig.doxyfile DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/DoxygenConfig.doxyfile "\nPROJECT_NUMBER = ${VERSION_SHORT}\nINPUT = ../\nOUTPUT_DIRECTORY = ${CMAKE_CURRENT_BINARY_DIR}/docs")
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/DoxygenConfig.doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
    if(MODEL_UTILITIES_INSTALL)
        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/html DESTINATION docs COMPONENT documentation)
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/docs/htmldocs.html DESTINATION docs COMPONENT documentation)
    endif()
endif()

include(GenerateExportHeader)
include(GNUInstallDirs)
add_library(QBbgLib  ${qbbglib_HEADERS} ${qbbglib_PRIVATE_HEADERS} ${qbbglib_SRCS})
add_library(QBbgLib::QBbgLib ALIAS QBbgLib)
generate_export_header(QBbgLib
    STATIC_DEFINE QBBGLIB_STATIC
    EXPORT_MACRO_NAME QBBGLIB_EXPORT
    EXPORT_FILE_NAME globaldefs/qbbglib_global.h
)
target_include_directories(QBbgLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/globaldefs>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(QBbgLib PUBLIC QBBGLIB_STATIC)
endif()
target_compile_definitions(QBbgLib PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)
target_link_libraries(QBbgLib PUBLIC Qt${QT_VERSION_MAJOR}::Core)
if(QBBGLIB_OFFLINE)
    target_compile_definitions(QBbgLib PUBLIC QBbg_OFFLINE)
else()
    target_link_libraries(QBbgLib PUBLIC Blpapi::Blpapi)
endif()
set_target_properties(QBbgLib PROPERTIES
    AUTOMOC ON
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN TRUE
    SOVERSION ${VERSION_MAJOR}
    VERSION ${VERSION_SHORT}
    EXPORT_NAME "QBbgLib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${qbbglib_PlatformDir}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${qbbglib_PlatformDir}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${qbbglib_PlatformDir}/bin"
)
if(MODEL_UTILITIES_INSTALL)
    install(FILES ${modelutilities_INSTALL_INCLUDE} "${CMAKE_CURRENT_BINARY_DIR}/globaldefs/qbbglib_global.h"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT QBbgLib_Development
    )
    install(TARGETS QBbgLib
        EXPORT QBbgLibTargets
        RUNTIME
            DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT QBbgLib_Runtime
        LIBRARY
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT QBbgLib_Runtime
            NAMELINK_SKIP
        INCLUDES
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        ARCHIVE
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT QBbgLib_Development
    )
    if(BUILD_SHARED_LIBS)
        install(TARGETS QBbgLib
            EXPORT QBbgLibTargets
            LIBRARY
                DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT QBbgLib_Development
                NAMELINK_ONLY
        )
    endif()
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file("QBbgLibConfigVersion.cmake"
        VERSION ${VERSION_SHORT}
        COMPATIBILITY SameMajorVersion
    )
    install(EXPORT QBbgLibTargets
            FILE QBbgLibTargets.cmake
            NAMESPACE QBbgLib::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QBbgLib
            COMPONENT QBbgLib_Development
    )
    install(FILES "QBbgLibConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/QBbgLibConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QBbgLib
        COMPONENT QBbgLib_Development
    )
endif()
