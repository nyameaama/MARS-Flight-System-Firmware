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

#include "_nav.h"

double NAVIGATION_STACK::COMPUTE_BEARING(double current_lat,double current_long,double final_lat,double final_long){
	UTILITY_FUNCTIONS *convert = new UTILITY_FUNCTIONS;
    double temp1,temp2,bearing;
	temp1 = sin(final_long - current_long) * cos(final_lat);
	temp2 = cos(current_lat) * sin(final_lat) -  sin(current_lat) * cos(final_lat) * cos(final_long - current_long);
	bearing = atan2(temp2, convert -> rad2deg(temp1));
	delete convert;
	return bearing;
}

double NAVIGATION_STACK::DISTANCE_BETWEEN(double current_lat,double current_long,double final_lat,double final_long){
	UTILITY_FUNCTIONS *convert = new UTILITY_FUNCTIONS;
    double theta, dist;
	if ((current_lat == final_lat) && (current_long == final_long)){
		return 0;
	}
	else{
		theta = current_long - final_long;
		dist = sin(convert -> deg2rad(current_lat)) * sin(convert -> deg2rad(final_lat)) + cos(convert -> deg2rad(current_lat)) * cos(convert -> deg2rad(final_lat)) * cos(convert -> deg2rad(theta));
		dist = acos(dist);
		dist = convert -> rad2deg(dist);
		dist = dist * 60 * 1.1515;
		dist = dist * 1.609344;
		delete convert;
		return (dist);
	}
}

