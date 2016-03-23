#################################################################################
# This file is part of QBbgLib.                                                 #
#                                                                               #
# QBbgLib is free software: you can redistribute it and/or modify               #
# it under the terms of the GNU Lesser General Public License as published by   #
# the Free Software Foundation, either version 3 of the License, or             #
# (at your option) any later version.                                           #
#                                                                               #
# QBbgLib is distributed in the hope that it will be useful,                    #
# but WITHOUT ANY WARRANTY; without even the implied warranty of                #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 #
# GNU Lesser General Public License for more details.                           #
#                                                                               #
# You should have received a copy of the GNU Lesser General Public License      #
# along with QBbgLib.  If not, see <http://www.gnu.org/licenses/>.              #
#################################################################################

TEMPLATE = lib
isEmpty(PREFIX) {
 warning("PREFIX not specified")
 PREFIX = ../QBbgLib
}
win32{
    win64{
        COMPILING64 = true
    }
    else{
        COMPILING64 = false
    }
}
else {
    COMPILING64 = contains($$system(getconf LONG_BIT), 64)
}
if(COMPILING64){
    message("Compiling 64 bit")
}
else{
    message("Compiling 32 bit")
}
CONFIG(debug, debug|release) {
    mac: TARGET = QBbgLib_debug
    win32: TARGET = QBbgLibd
    DESTDIR = ../bin/Debug
    MOC_DIR += ./GeneratedFiles/debug
    OBJECTS_DIR += debug
}
CONFIG(release, debug|release) {
    TARGET = QBbgLib
    DESTDIR = ../bin/Release
    MOC_DIR += ./GeneratedFiles/release
    OBJECTS_DIR += release
}
QT += core
DEFINES += QBBG_LIB_BUILD QT_DLL QBBGLIB_LIB
INCLUDEPATH += $(BLPPATH)/include \
    ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
LIBS += -L"$(BLPPATH)/lib"
if (COMPILING64){
    LIBS += -lblpapi3_64
}
else{
    LIBS += -lblpapi3_32
}
DEPENDPATH += .
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
CONFIG += build_all
if (COMPILING64){
    target.path = $$PREFIX/lib64
}
else{
    target.path = $$PREFIX/lib32
}
headers.path=$$PREFIX/include
headers.files = *.h
headers.files += ./Includes/*
INSTALLS += headers target
include(QBbgLib.pri)
