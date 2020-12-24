/*
 * Copyright (c) 2007 Ivan Leben
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library in the file COPYING;
 * if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/*--------------------------------------------
 * Definitions of all the arrays used
 *--------------------------------------------*/

#include "shArrays.h"

#define _ITEM_T  SHfloat
#define _ARRAY_T SHFloatArray
#define _FUNC_T  shFloatArray
#define _ARRAY_DEFINE
#include "shArrayBase.h"

#define _ITEM_T  SHRectangle
#define _ARRAY_T SHRectArray
#define _FUNC_T  shRectArray
#define _COMPARE_T(x,y) 1
#define _ARRAY_DEFINE
#include "shArrayBase.h"
