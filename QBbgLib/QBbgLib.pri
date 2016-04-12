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
# along with QBbgLib.  If not, see < http://www.gnu.org/licenses/ >.            #
#################################################################################

HEADERS += ./QBbgProjectGlobals.h \
    ./QBbgSecurity.h \
    ./QBbgManager.h \
    ./QBbgOverride.h \
    ./QBbgRequestGroup.h \
    ./QBbgAbstractFieldRequest.h \
    ./QBbgAbstractRequest.h \
    ./QBbgHistoricalDataRequest.h \
    ./QBbgPortfolioDataRequest.h \
    ./QBbgAbstractIntradayRequest.h \
    ./QbbgReferenceDataRequest.h \
    ./QBbgAbstractFieldResponse.h \
    ./QBbgAbstractResponse.h \
    ./QBbgHistoricalDataResponse.h \
    ./QBbgPortfolioDataResponse.h \
    ./QBbgReferenceDataResponse.h \
    ./private/QBbgAbstractFieldRequest_p.h \
    ./private/QBbgAbstractFieldResponse_p.h \
    ./private/QBbgAbstractIntradayRequest_p.h \
    ./private/QBbgAbstractRequest_p.h \
    ./private/QBbgAbstractResponse_p.h \
    ./private/QBbgHistoricalDataRequest_p.h \
    ./private/QBbgHistoricalDataResponse_p.h \
    ./private/QBbgManager_p.h \
    ./private/QBbgOverride_p.h \
    ./private/QBbgPortfolioDataRequest_p.h \
    ./private/QBbgPortfolioDataResponse_p.h \
    ./private/QBbgReferenceDataRequest_p.h \
    ./private/QBbgReferenceDataResponse_p.h \
    ./private/QBbgRequestGroup_p.h \
    ./private/QBbgSecurity_p.h \
    ./private/QBbgWorkerThread_p.h \
    ./private/QBbgAbstractWorker_p.h \
    ./private/QBbgRequestResponseWorker_p.h \
    ./QBbgIntradayTickRequest.h \
    ./private/QBbgIntradayTickRequest_p.h \
    ./private/QBbgAbstractIntradayResponse_p.h \
    ./QBbgAbstractIntradayResponse.h \
    ./QBbgIntradayTickResponse.h \
    ./private/QBbgIntradayTickResponse_p.h
SOURCES += ./QBbgManager.cpp \
    ./QBbgOverride.cpp \
    ./QBbgSecurity.cpp \
    ./QBbgAbstractRequest.cpp \
    ./QBbgHistoricalDataRequest.cpp \
    ./QBbgAbstractIntradayRequest.cpp \
    ./QBbgPortfolioDataRequest.cpp \
    ./QBbgReferenceDataRequest.cpp \
    ./QBbgRequestGroup.cpp \
    ./QBbgAbstractFieldRequest.cpp \
    ./QBbgAbstractFieldResponse.cpp \
    ./QBbgAbstractResponse.cpp \
    ./QBbgHistoricalDataResponse.cpp \
    ./QBbgPortfolioDataResponse.cpp \
    ./QBbgReferenceDataResponse.cpp \
    ./private/QBbgWorkerThread.cpp \
    ./private/QBbgAbstractWorker.cpp \
    ./private/QBbgRequestResponseWorker.cpp \
    ./QBbgIntradayTickRequest.cpp \
    ./QBbgAbstractIntradayResponse.cpp \
    ./QBbgIntradayTickResponse.cpp
