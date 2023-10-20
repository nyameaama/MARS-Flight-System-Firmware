#include "_ptam.h"

SharedMemory::SharedMemory() {}

SharedMemory::~SharedMemory() {}

SharedMemory& SharedMemory::getInstance() {
    static SharedMemory instance;
    return instance;
}

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

void SharedMemory::clearData(const std::string& id) {
    std::lock_guard<std::mutex> lock(mutex_);
    stringData_.erase(id);
    doubleData_.erase(id);
    intData_.erase(id);
}

void SharedMemory::clearAllData() {
    std::lock_guard<std::mutex> lock(mutex_);
    stringData_.clear();
    doubleData_.clear();
    intData_.clear();
}

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

std::string SharedMemory::getLastElement(const std::vector<std::string>& vec) {
    return vec.empty() ? "" : vec.back();
}

double SharedMemory::getLastElement(const std::vector<double>& vec) {
    return vec.empty() ? 0.0 : vec.back();
}

int SharedMemory::getLastElement(const std::vector<int>& vec) {
    return vec.empty() ? 0 : vec.back();
}