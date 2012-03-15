//
// Copyright (C) 2011-2012 by Daniel Buckmaster (dan.buckmaster@gmail.com)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

/// @file AesopDemo.h
/// @brief Include data for the Aesop demo application.

#ifndef _AESOPDEMO_H_
#define _AESOPDEMO_H_

#include "Aesop.h"

using namespace Aesop;

/// @brief Implement the AesopContext interface and just print events to the
///        console. We also provide a 'flying' flag that will allow the planner
///        to travel between any two locations.
class AesopDemoContext : public Context {
public:
   void logEvent(const char *fmt, ...);

   /// @brief Default constructor.
   AesopDemoContext();
   ~AesopDemoContext();
protected:
private:
};

/// @brief Implement the Action interface for a two-parameter movement action.
class MoveAction : public Action {
public:
   MoveAction(std::string name, float cost = 1.0f);
   void getParams(Context *ctx, const paramlist &plist, paramset &pset) const;
};

/// @brief Implement the Action interface for a two-parameter flying movement
///        action.
class FlyAction : public Action {
public:
	FlyAction(std::string name, float cost = 1.0f);
	void getParams(Context *ctx, const paramlist &plist, paramset &pset) const;
};

#endif
