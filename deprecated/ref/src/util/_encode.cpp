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

#include"_encode.h"

// Encodes two or more items of any datatype as a single string
  template<typename T, typename... Ts>
  std::string EncoderDecoder::encode(const T& first, const Ts&... rest) {
    std::ostringstream oss;
    encodeHelper(oss, first, rest...);
    return oss.str();
  }

// Decodes the data back to its original items of data
  template<typename T, typename... Ts>
  std::tuple<T, Ts...> EncoderDecoder::decode(const std::string& encoded) {
    std::istringstream iss(encoded);
    return std::tuple<T, Ts...>(decodeHelper<T>(iss), decodeHelper<Ts>(iss)...);
  }

// Helper method to encode items recursively
  template<typename T, typename... Ts>
  void EncoderDecoder::encodeHelper(std::ostringstream& oss, const T& first, const Ts&... rest) {
    oss << first << DELIMITER;
    encodeHelper(oss, rest...);
  }

// Base case for encoding
  void EncoderDecoder::encodeHelper(std::ostringstream& oss) {}

// Helper method to decode items recursively
  template<typename T>
  T EncoderDecoder::decodeHelper(std::istringstream& iss) {
    T val;
    iss >> val;
    return val;
  }

