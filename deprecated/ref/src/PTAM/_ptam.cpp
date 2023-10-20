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

std::unordered_map<std::string, std::vector<void*>>* DataStore::data_map = nullptr;

void DataStore::storeData(const std::string& id, const std::string& data) {
    if (!data_map) {
        data_map = new std::unordered_map<std::string, std::vector<void*>>();
    }
    (*data_map)[id].push_back(new std::string(data));
}

void DataStore::storeData(const std::string& id, int data) {
    if (!data_map) {
        data_map = new std::unordered_map<std::string, std::vector<void*>>();
    }
    (*data_map)[id].push_back(new int(data));
}

void DataStore::storeData(const std::string& id, double data) {
    if (!data_map) {
        data_map = new std::unordered_map<std::string, std::vector<void*>>();
    }
    (*data_map)[id].push_back(new double(data));
}

std::vector<std::string> DataStore::getStringData(const std::string& id) {
    std::vector<std::string> results;
    if (data_map && data_map->count(id) > 0) {
        for (void* ptr : (*data_map)[id]) {
            std::string* data_ptr = static_cast<std::string*>(ptr);
            results.push_back(*data_ptr);
        }
    }
    return results;
}

std::vector<int> DataStore::getIntData(const std::string& id) {
    std::vector<int> results;
    if (data_map && data_map->count(id) > 0) {
        for (void* ptr : (*data_map)[id]) {
            int* data_ptr = static_cast<int*>(ptr);
            results.push_back(*data_ptr);
        }
    }
    return results;
}

std::vector<double> DataStore::getDoubleData(const std::string& id) {
    std::vector<double> results;
    if (data_map && data_map->count(id) > 0) {
        for (void* ptr : (*data_map)[id]) {
            double* data_ptr = static_cast<double*>(ptr);
            results.push_back(*data_ptr);
        }
    }
    return results;
}

void DataStore::clearData(const std::string& id) {
    if (data_map && data_map->count(id) > 0) {
        for (void* ptr : (*data_map)[id]) {
            delete static_cast<std::string*>(ptr);
        }
        (*data_map)[id].clear();
    }
}

void DataStore::clearData() {
    if (data_map) {
        for (auto& pair : *data_map) {
            for (void* ptr : pair.second) {
                if (ptr != nullptr) {
                    delete ptr;
                }
            }
        }
        delete data_map;
        data_map = nullptr;
    }
}

DataStore::~DataStore() {
    clearData();
}