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

TARGET = QBbgLib
contains(DEFINES, QBbg_OFFLINE){
    TARGET = $$join(TARGET,,,Off) 
}
CONFIG(debug, debug|release) {
    mac: TARGET = $$join(TARGET,,,_debug) 
    win32: TARGET = $$join(TARGET,,,d)
    DESTDIR = ../bin/Debug
    MOC_DIR += ./GeneratedFiles/debug
    OBJECTS_DIR += debug
}
CONFIG(release, debug|release) {
    DESTDIR = ../bin/Release
    MOC_DIR += ./GeneratedFiles/release
    OBJECTS_DIR += release
}
QT += core
DEFINES += QBBG_LIB_BUILD QT_DLL QBBGLIB_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
!contains(DEFINES, QBbg_OFFLINE) {
    INCLUDEPATH += $(BLPPATH)/include 
    LIBS += -L"$(BLPPATH)/lib"
    contains(QMAKE_TARGET.arch, x86_64){
        LIBS += -lblpapi3_64
    }
    else{
        LIBS += -lblpapi3_32
    }
}
DEPENDPATH += .
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
CONFIG += build_all
contains(QMAKE_TARGET.arch, x86_64){
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
