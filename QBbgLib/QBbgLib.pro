TEMPLATE = lib
isEmpty(PREFIX) {
 warning("PREFIX not specified")
 PREFIX = ../QBbgLib
}
CONFIG(debug, debug|release) {
    win32: TARGETNAME=QBbgLibd
	mac: TARGETNAME=QBbgLib_debug
    DESTDIRNAME = ../Win32/Debug
    MOC_DIR += ./GeneratedFiles/debug
    OBJECTS_DIR += debug
}
CONFIG(release, debug|release) {
    TARGETNAME = QBbgLib
    DESTDIRNAME = ../Win32/Release
    MOC_DIR += ./GeneratedFiles/release
    OBJECTS_DIR += release
}
TARGET=$$TARGETNAME
DESTDIR=$$DESTDIRNAME
QT += core
DEFINES += QBBG_LIB_BUILD WIN64 QT_DLL QBBGLIB_LIB
INCLUDEPATH += $(BLPPATH)/include \
    ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
LIBS += -L"$(BLPPATH)/lib" \
    -lblpapi3_32
DEPENDPATH += .
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
installbin.path=$$PREFIX/lib
installinclude.path=$$PREFIX/include
installinclude.files = $$HEADERS
INSTALLS = installbin installinclude
include(QBbgLib.pri)
