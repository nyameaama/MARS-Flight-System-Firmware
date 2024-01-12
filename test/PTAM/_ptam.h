/**
 * @file _ptam.h
 * @brief Program Temporary Access Memory
 *
 * Store data from various subsystems inside PTAM registers to avoid the
 * overhead of directly requesting data from subsystems.
 *
 * @date August 18th 2023
 * @copyright Copyright (c) 2023 limitless Aeronautics
 *            This file is part of the MARS Flight System Firmware
 *
 * @authors  Nyameaama Gambrah, Lukas Jackson
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

#ifndef DATASTORE_HPP
#define DATASTORE_HPP

/* System includes */
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

/* Logger includes */
#include "../Logging/logger.hpp"

class DataStore
{
  private:
    static std::unordered_map<std::string, std::vector<void*>>* data_map;

  public:
    static void storeData(const std::string& id, const std::string& data);
    static void storeData(const std::string& id, int data);
    static void storeData(const std::string& id, double data);

    static std::vector<std::string> getStringData(const std::string& id);
    static std::vector<int> getIntData(const std::string& id);
    static std::vector<double> getDoubleData(const std::string& id);

    static void clearData(const std::string& id);
    static void clearData();
    ~DataStore();
};

#endif  // DATASTORE_HPP
