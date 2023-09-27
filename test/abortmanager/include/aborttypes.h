/**
 * @file aborttypes.h
 * @brief Abort manager types
 *
 *
 * @date September 15th 2023
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

#ifndef ABORT_TYPES_H
#define ABORT_TYPES_H

#include<inttypes.h>
#include<string>

// Define macros for abort_t values
#define LOSS_OF_CONTROL         0
#define BAD_SENSOR_DATA         0
#define UNEXPECTED_LOW_BATTERY  0
#define FAR_OFF_COURSE          0

#define NO_LOSS_OF_CONTROL      1
#define NO_BAD_SENSOR_DATA      1
#define NO_UNEXPECTED_LOW_BATTERY 1
#define NOT_OFF_COURSE            1

typedef uint8_t abort_t;  // Use uint8_t directly as the type for abort_t

typedef struct
{
    std::string name;
    double data;
    abort_t vstatus;
} weighted_t;

struct Vector3D
{
    double lat;
    double lon;
    double alt;
};

#endif /* ABORT_TYPES_H */
