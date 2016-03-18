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
LIBS += -L"$(BLPPATH)/lib" \
    -lblpapi3_32
DEPENDPATH += .
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
CONFIG += build_all
target.path = $$PREFIX/lib
unix:!symbian {
	target.path=$$PREFIX/lib/$${LIB_ARCH}
}
headers.path=$$PREFIX/include
headers.files = *.h
headers.files += ./Includes/*
INSTALLS += headers target
include(QBbgLib.pri)
