/*MIT License
Copyright (c) 2023 limitless Aeronautics
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>

class SharedMemory {
public:
    static SharedMemory& getInstance();

    void storeString(const std::string& id, const std::string& data);
    void storeDouble(const std::string& id, double data);
    void storeInt(const std::string& id, int data);

    std::vector<std::string> getStringData(const std::string& id);
    std::vector<double> getDoubleData(const std::string& id);
    std::vector<int> getIntData(const std::string& id);

    void clearData(const std::string& id);
    void clearAllData();

    std::string getLastString(const std::string& id);
    double getLastDouble(const std::string& id);
    int getLastInt(const std::string& id);

private:
    SharedMemory();
    ~SharedMemory();

    std::unordered_map<std::string, std::vector<std::string>> stringData_;
    std::unordered_map<std::string, std::vector<double>> doubleData_;
    std::unordered_map<std::string, std::vector<int>> intData_;

    std::mutex mutex_;

private:
    std::string getLastElement(const std::vector<std::string>& vec);
    double getLastElement(const std::vector<double>& vec);
    int getLastElement(const std::vector<int>& vec);
};

#endif // SHARED_MEMORY_H