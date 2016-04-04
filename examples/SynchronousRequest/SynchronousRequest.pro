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

TEMPLATE = app
TARGET = SynchronousRequest
QT += core
DEFINES += QT_DLL
INCLUDEPATH += ../../QBbgLib \
    ./GeneratedFiles \
    .
CONFIG(debug, debug|release) {
    DESTDIR = ../bin/Debug
    INCLUDEPATH += ./GeneratedFiles/Debug
    MOC_DIR += ./GeneratedFiles/debug
    OBJECTS_DIR += debug
    LIBS += -L"../../bin/Debug"
    LIBS += -lQBbglibd
}
CONFIG(release, debug|release) {
    TARGET = SynchronousRequest
    INCLUDEPATH += ./GeneratedFiles/release
    DESTDIR = ../bin/Release
    MOC_DIR += ./GeneratedFiles/release
    OBJECTS_DIR += release
    LIBS += -L"../../bin/Release"
    LIBS += -lQBbglib
}
DEPENDPATH += .
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
CONFIG += build_all
SOURCES += ./SynchronousRequest.cpp
