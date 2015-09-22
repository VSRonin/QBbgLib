TEMPLATE = lib
isEmpty(PREFIX) {
 warning("PREFIX not specified")
 PREFIX = ../QBbgLib
}
CONFIG(debug, debug|release) {
    win32: TARGETNAME=QBbgLibd
	mac: TARGETNAME=QBbgLib_debug
    DESTDIRNAME = ../bin/Debug
    MOC_DIR += ./GeneratedFiles/debug
    OBJECTS_DIR += debug
}
CONFIG(release, debug|release) {
    TARGETNAME = QBbgLib
    DESTDIRNAME = ../bin/Release
    MOC_DIR += ./GeneratedFiles/release
    OBJECTS_DIR += release
}
TARGET=$$TARGETNAME
DESTDIR=$$DESTDIRNAME
QT += core
DEFINES += QBBG_LIB_BUILD QT_DLL QBBGLIB_LIB
INCLUDEPATH += $(BLPPATH)/include \
    ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
LIBS += -L"$(BLPPATH)/lib" \
    -lblpapi3_32
DEPENDPATH += .
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
target.path=$$PREFIX/lib
unix:!symbian {
	target.path=$$PREFIX/lib/$${LIB_ARCH}
}
target.files = $$DESTDIRNAME/*.dll
target.files += $$DESTDIRNAME/*.lib
target.files += $$DESTDIRNAME/*.pdb
headers.path=$$PREFIX/include
headers.files = *.h
headers.files += ./Includes/*
INSTALLS += headers target
include(QBbgLib.pri)
