/**
 * @file sender.c
 * @brief ESP-NOW sender function prototypes 
 *
 *
 * @date Febuary 25th, 2024
 * @copyright Copyright (c) 2023 Limitless Aeronautics
 *
 * @author Lukas R. Jackson, Nyameaama Gambrah
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
#include <stdio.h>
#include "sender.h"

// Function to introduce a delay
void delay(int seconds) {
    volatile int i, j;

    for (i = 0; i < seconds; i++) {
        for (j = 0; j < 1000000; j++) {
            // Adding some computation to prevent compiler optimization
            int temp = i + j;
            temp = temp * 2;
        }
    }
}

int main() {
    int duration = 5000;  // Set the duration of the timer in seconds

    printf("Starting timer for %d seconds...\n", duration);
    
    // Call the delay function to simulate the timer
    delay(duration);

    printf("Timer expired!\n");

    return 0;
}
