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

HEADERS += ./private/QBbgAbstractWorker_p.h \
    ./QBbgOverride.h \
    ./QBbgProjectGlobals.h \
    ./QBbgSecurity.h \
    ./QBbgManager.h \
    ./QBbgAbstractRequest.h \
    ./QBbgHistoricalDataRequest.h \
    ./QBbgPortfolioDataRequest.h \
    ./QbbgReferenceDataRequest.h \
    ./QBbgRequestGroup.h \
    ./QBbgAbstractFieldRequest.h \
    ./QBbgAbstractFieldResponse.h \
    ./QBbgAbstractResponse.h \
    ./QBbgHistoricalDataResponse.h \
    ./QBbgPortfolioDataResponse.h \
    ./QBbgReferenceDataResponse.h \
    ./private/QBbgWorkerThread_p.h \
    ./private/QBbgRequestResponseWorker_p.h \
    ./private/QBbgAbstractFieldRequest_p.h \
    ./private/QBbgAbstractFieldResponse_p.h \
    ./private/QBbgAbstractRequest_p.h \
    ./private/QBbgAbstractResponse_p.h \
    ./private/QBbgHistoricalDataRequest_p.h \
    ./private/QBbgHistoricalDataResponse_p.h \
    ./private/QBbgManager_p.h \
    ./private/QBbgOverride_p.h \
    ./private/QBbgPortfolioDataRequest_p.h \
    ./private/QBbgPortfolioDataResponse_p.h \
    ./private/QbbgReferenceDataRequest_p.h \
    ./private/QBbgReferenceDataResponse_p.h \
    ./private/QBbgRequestGroup_p.h \
    ./private/QBbgSecurity_p.h
SOURCES += ./QBbgManager.cpp \
    ./QBbgOverride.cpp \
    ./QBbgRequestGroup.cpp \
    ./QBbgSecurity.cpp \
    ./private/QBbgAbstractWorker.cpp \
    ./QBbgAbstractRequest.cpp \
    ./QBbgHistoricalDataRequest.cpp \
    ./QBbgPortfolioDataRequest.cpp \
    ./QbbgReferenceDataRequest.cpp \
    ./QBbgAbstractFieldRequest.cpp \
    ./QBbgAbstractFieldResponse.cpp \
    ./QBbgAbstractResponse.cpp \
    ./QBbgHistoricalDataResponse.cpp \
    ./QBbgPortfolioDataResponse.cpp \
    ./QBbgReferenceDataResponse.cpp \
    ./private/QBbgRequestResponseWorker.cpp \
    ./private/QBbgWorkerThread.cpp
