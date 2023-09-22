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

#include "_ptam.h"

SharedMemory::SharedMemory() {}

SharedMemory::~SharedMemory() {}

//____________________________________________________________
/* Main subroutine -> initialises PTAM instance
===========================================================================
void
===========================================================================
*/
SharedMemory& SharedMemory::getInstance() {
    static SharedMemory instance;
    return instance;
}

//____________________________________________________________
/* Main subroutines -> stores value of datatypes (std::string, double, int)
===========================================================================
|    Designated ID   This creates the PTAM register with this ID an can only be referenced with this ID string
|    Data Value      Data value of types std::string, double, int
===========================================================================
*/
void SharedMemory::storeString(const std::string& id, const std::string& data) {
    std::lock_guard<std::mutex> lock(mutex_);
    stringData_[id].push_back(data);
}

void SharedMemory::storeDouble(const std::string& id, double data) {
    std::lock_guard<std::mutex> lock(mutex_);
    doubleData_[id].push_back(data);
}

void SharedMemory::storeInt(const std::string& id, int data) {
    std::lock_guard<std::mutex> lock(mutex_);
    intData_[id].push_back(data);
}

//____________________________________________________________
/* Main subroutines -> retrieves all the values from PTAM register of appropriate typdef
===========================================================================
|   Designated ID   This references the PTAM register assigned with this ID
===========================================================================
*/
std::vector<std::string> SharedMemory::getStringData(const std::string& id) {
    std::lock_guard<std::mutex> lock(mutex_);
    return stringData_[id];
}

std::vector<double> SharedMemory::getDoubleData(const std::string& id) {
    std::lock_guard<std::mutex> lock(mutex_);
    return doubleData_[id];
}

std::vector<int> SharedMemory::getIntData(const std::string& id) {
    std::lock_guard<std::mutex> lock(mutex_);
    return intData_[id];
}

//____________________________________________________________
/* Main subroutine -> Clear data in specific PTAM register
===========================================================================
|    Designated ID   This references the PTAM register assigned with this ID
===========================================================================
*/
void SharedMemory::clearData(const std::string& id) {
    std::lock_guard<std::mutex> lock(mutex_);
    stringData_.erase(id);
    doubleData_.erase(id);
    intData_.erase(id);
}

//____________________________________________________________
/* Main subroutine -> Clear data in all PTAM registers
===========================================================================
|    void
===========================================================================
*/
void SharedMemory::clearAllData() {
    std::lock_guard<std::mutex> lock(mutex_);
    stringData_.clear();
    doubleData_.clear();
    intData_.clear();
}

//____________________________________________________________
/* Main subroutines -> retrieves the last and most recent value in PTAM register of appropriate typdef
===========================================================================
|    Designated ID   This references the PTAM register assigned with this ID
===========================================================================
*/
std::string SharedMemory::getLastString(const std::string& id) {
    std::lock_guard<std::mutex> lock(mutex_);
    return getLastElement(stringData_[id]);
}

double SharedMemory::getLastDouble(const std::string& id) {
    std::lock_guard<std::mutex> lock(mutex_);
    return getLastElement(doubleData_[id]);
}

int SharedMemory::getLastInt(const std::string& id) {
    std::lock_guard<std::mutex> lock(mutex_);
    return getLastElement(intData_[id]);
}

//____________________________________________________________
/* Utillity subroutines -> Retrieve last element in a vectors
===========================================================================
|    typdef -> std::vector
===========================================================================
*/
std::string SharedMemory::getLastElement(const std::vector<std::string>& vec) {
    return vec.empty() ? "" : vec.back();
}

double SharedMemory::getLastElement(const std::vector<double>& vec) {
    return vec.empty() ? 0.0 : vec.back();
}

int SharedMemory::getLastElement(const std::vector<int>& vec) {
    return vec.empty() ? 0 : vec.back();
}