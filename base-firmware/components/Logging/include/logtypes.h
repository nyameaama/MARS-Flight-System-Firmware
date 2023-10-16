/**
 * @file logtypes.h
 * @brief log types for logger
 *
 * Declared types for the logger and can be used as an API for other subsystems
 *
 * @date August 18th 2023
 * @copyright Copyright (c) 2023 limitless Aeronautics
 *
 * @author Lukas Jackson
 *
 * @license MIT License
 *          Copyright (c) 2023 limitless Aeronautics
 *          Permission is hereby granted, free of charge, to any person obtaining a copy
 *          of this software and associated documentation files (the "Software"), to deal
 *          in the Software without restriction, including without limitation the rights
 *          to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *          copies of the Software, and to permit persons to whom the Software is
 *          furnished to do so, subject to the following conditions:
 *          The above copyright notice and this permission notice shall be included in all
 *          copies or substantial portions of the Software.
 *          THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *          IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *          FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *          AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *          LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *          OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *          SOFTWARE.
 */


#ifndef LOGTYPES_H_
#define LOGTYPES_H_

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdio> // Include the C standard I/O library for printf
#include<cstdint> // For uint types

/**
 * @brief mars expected return types
 *
 * @param ROUTINE_SOFT_FAIL
 * @param ROUTINE_HARD_FAIL
 *
 */
struct mars_exception_t
{
    enum Type : uint8_t {
        ROUTINE_SOFT_FAIL,
        ROUTINE_HARD_FAIL
    };
}__attribute__((packed));


#endif /* LOGTYPES_H_ */