/*******************************************************************************\
* This file is part of QBbgLib.                                                 *
*                                                                               *
* QBbgLib is free software : you can redistribute it and / or modify            *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation, either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* QBbgLib is distributed in the hope that it will be useful,                    *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the                   *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with QBbgLib.If not, see < http://www.gnu.org/licenses/>.               *
*                                                                               *
\*******************************************************************************/

#ifndef ProjectGlobals_h__
#define ProjectGlobals_h__
#ifdef _DEBUG
//#define PRINT_RESPONSE_MESSAGE //Uncomment to debug response messages from Bloomberg
#endif // _DEBUG
#ifdef QBBG_LIB_BUILD
    #define QBBG_EXPORT __declspec(dllexport)
    #define QBBG_EXTERN 
#else
    #define QBBG_EXPORT __declspec(dllimport)
    #define QBBG_EXTERN extern
#endif // QBBG_LIB_BUILD
#endif