# Locates the Bloomberg API C++ SDK. Set BLPAPI_ROOT (CMake or environment variable) to the
# unpacked SDK folder, the one containing include/ and lib/.
#
# Defines the imported target Blpapi::Blpapi.

find_path(Blpapi_INCLUDE_DIR blpapi_session.h
    HINTS ${Blpapi_ROOT} ENV Blpapi_ROOT
    PATH_SUFFIXES include)

find_library(Blpapi_LIBRARY NAMES blpapi3_64
    HINTS ${Blpapi_ROOT} ENV Blpapi_ROOT
    PATH_SUFFIXES lib)

# Only look inside the SDK: the copy in C:\blp\DAPI belongs to the Terminal and may be a different version.
find_file(Blpapi_DLL NAMES blpapi3_64.dll
    HINTS ${Blpapi_ROOT} ENV Blpapi_ROOT
    PATH_SUFFIXES lib bin
    NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Blpapi
    REQUIRED_VARS Blpapi_LIBRARY Blpapi_INCLUDE_DIR Blpapi_DLL)

if(Blpapi_FOUND AND NOT TARGET Blpapi::Blpapi)
    add_library(Blpapi::Blpapi SHARED IMPORTED)
    set_target_properties(Blpapi::Blpapi PROPERTIES
        IMPORTED_LOCATION "${Blpapi_DLL}"
        IMPORTED_IMPLIB "${Blpapi_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${Blpapi_INCLUDE_DIR}")
endif()

mark_as_advanced(Blpapi_INCLUDE_DIR Blpapi_LIBRARY Blpapi_DLL)
