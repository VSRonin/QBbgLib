TEMPLATE = lib
isEmpty(PREFIX) {
 PREFIX = ../QBbgLib
}
CONFIG(debug, debug|release) {
    TARGETNAME=QBbgLibd
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
installbin.files = $$DESTDIRNAME/TARGETNAME.dll
installbin.files += $$DESTDIRNAME/TARGETNAME.lib
installbin.files += $$DESTDIRNAME/TARGETNAME.exp
CONFIG(debug, debug|release) {
    installbin.files += $$DESTDIRNAME/TARGETNAME.pdb
}
installinclude.path=$$PREFIX/include
installinclude.files = ./*.h
INSTALLS += installbin
INSTALLS += installinclude
include(QBbgLib.pri)
