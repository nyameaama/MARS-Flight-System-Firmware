/*MIT License

Copyright (c) 2020 Nyameaama Gambrah

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

/*#include"_ptamAPI.h"

uint8_t PTAM::PTAM_ADD_BASE_DOUBLE(std::string baseID,double data){
    DataStore *obj = new DataStore();
    obj -> storeData(baseID,data);
    delete obj;
    return sizeof(data);
}

uint8_t PTAM::PTAM_ADD_BASE_INT(std::string baseID, int16_t data){
    DataStore *obj = new DataStore();
    obj -> storeData(baseID, data);
    delete obj;
    return sizeof(data);
}

uint8_t PTAM::PTAM_ADD_BASE_CHAR(std::string baseID, std::string data){
    DataStore *obj = new DataStore();
    obj -> storeData(baseID, data);
    delete obj;
    return sizeof(data);
}

std::vector<std::string> PTAM::PTAM_RETRIEVE_BASE_CHAR(std::string baseID){
    DataStore *obj = new DataStore();
    std::vector<std::string> id_data = obj -> getData<std::string>(baseID);
    delete obj;
    //Return the vector
    return id_data;
}

std::vector<int16_t> PTAM::PTAM_RETRIEVE_BASE_INT(std::string baseID){
    DataStore *obj = new DataStore();
    std::vector<int16_t> id_data  = obj -> getData<int16_t>(baseID);
    delete obj;
    //Return the vector
    return id_data;
}

std::vector<double> PTAM::PTAM_RETRIEVE_BASE_DOUBLE(std::string baseID){
    DataStore *obj = new DataStore();
    std::vector<double> id_data = obj -> getData<double>(baseID);
    delete obj;
    //Return the vector
    return id_data;
}

void PTAM::PTAM_CLEAR_ALL(){
    DataStore *obj = new DataStore();
    obj -> clearData();
    delete obj;
}
*/