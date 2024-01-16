/*MIT License

Copyright (c) 2023 Limitless Aeronautics

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

/*   Check for automatic takeoff conditions being met using the following sequence:
 *   1) Check for adequate GPS lock - if not return false
 *   2) Check the gravity compensated longitudinal acceleration against the threshold and start the
 * timer if true 3) Wait until the timer has reached the specified value (increments of 0.1 sec) and
 * then check the GPS speed against the threshold 4) If the GPS speed is above the threshold and the
 * attitude is within limits then return true and reset the timer 5) If the GPS speed and attitude
 * within limits has not been achieved after 2.5 seconds, return false and reset the timer 6) If the
 * time lapsed since the last timecheck is greater than 0.2 seconds, return false and reset the
 * timer NOTE : This function relies on the TECS 50Hz processing for its acceleration measure.
 */