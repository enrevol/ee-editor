/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __PLATFORM_CCPLATFORMDEFINE_H__
#define __PLATFORM_CCPLATFORMDEFINE_H__
/// @cond DO_NOT_SHOW

#include "platform/CCPlatformConfig.h"

#include <qglobal.h>

#undef CC_DLL
#ifdef _USRDLL
#ifdef Q_OS_WIN
#define CC_DLL __declspec(dllexport)
#else // Q_OS_WIN
#define CC_DLL Q_DECL_EXPORT
#endif // Q_OS_WIN
#else  // _USRDLL
#ifdef Q_OS_WIN
#define CC_DLL __declspec(dllimport)
#else // Q_OS_WIN
#define CC_DLL Q_DECL_IMPORT
#endif // Q_OS_WIN
#endif // _USRDLL

#include <cassert>

#if CC_DISABLE_ASSERT > 0
#define CC_ASSERT(cond)
#else // CC_DISABLE_ASSERT
#define CC_ASSERT(cond) assert(cond)
#endif // CC_DISABLE_ASSERT

#define CC_UNUSED_PARAM(unusedparam) static_cast<void>(unusedparam)

/// @endcond
#endif /* __PLATFORM_CCPLATFORMDEFINE_H__*/
