/**
 * @file unittestPTAM.cpp
 * @brief PTAM unit testing
 *
 * PTAM unit testing
 *
 * @date August >18th 2023
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
/* System includes */
#include <iostream>

/* Ptam includes */
#include "_ptam.h"

/* Google testing */
#include<gtest/gtest.h>


TEST(TestStoreData, Store_Str_Data){
    DataStore* obj = new DataStore();
    std::string stateDescript = "ARMED";

    obj->storeData("stateDescript", stateDescript);
    EXPECT_EQ("ARMED", stateDescript);

    std::vector<std::string> stringData = obj->getStringData("stateDescript");
    for (const std::string& element : stringData) {
        std::cout << element << std::endl;
    }
    EXPECT_EQ(stringData.size(), 1); // Assuming you expect only one element
    EXPECT_EQ(stringData[0], "ARMED");
}

TEST(TestStoreData, Store_Int_Data){
    DataStore* obj = new DataStore();
    int count = 10;

    obj->storeData("Count", count);
    EXPECT_EQ(10, count);

    std::vector<int> intData = obj->getIntData("Count");
    auto var = intData.back();
    EXPECT_EQ(var, count);

    std::cout << var << std::endl;
}

TEST(TestStoreData, Store_Doub_Data){
    DataStore* obj = new DataStore();
    double value = 3.14;

    obj->storeData("value", value);
    EXPECT_EQ(3.14, value);

    std::vector<double> doubleData = obj->getDoubleData("value");
    for (const double& element : doubleData) {
        std::cout << element << std::endl;
    }
    EXPECT_EQ(doubleData.size(), 1); // Assuming you expect only one element
    EXPECT_EQ(doubleData[0], value);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
