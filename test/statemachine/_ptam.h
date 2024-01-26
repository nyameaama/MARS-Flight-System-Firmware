#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

/* System includes */
#include <iostream>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

/* logger includes */
//#include "../Logging/logger.hpp"

class SharedMemory
{
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

#endif  // SHARED_MEMORY_H