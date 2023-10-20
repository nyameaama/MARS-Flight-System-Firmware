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

#ifndef ENCODER_DECODER_HPP
#define ENCODER_DECODER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

class EncoderDecoder {
public:
  // Encodes two or more items of any datatype as a single string
  template<typename T, typename... Ts>
  static std::string encode(const T& first, const Ts&... rest);

  // Decodes the data back to its original items of data
  template<typename T, typename... Ts>
  static std::tuple<T, Ts...> decode(const std::string& encoded);

private:
  // Helper method to encode items recursively
  template<typename T, typename... Ts>
  static void encodeHelper(std::ostringstream& oss, const T& first, const Ts&... rest);

  // Base case for encoding
  static void encodeHelper(std::ostringstream& oss);

  // Helper method to decode items recursively
  template<typename T>
  static T decodeHelper(std::istringstream& iss);

  // The delimiter used to separate encoded items
  static const char DELIMITER = '|';
};

#endif // ENCODER_DECODER_HPP