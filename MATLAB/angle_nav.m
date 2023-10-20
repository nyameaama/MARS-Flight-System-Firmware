%{
    MIT License
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
SOFTWARE.
%}
%Test Data

%function compute_Angle()
pathInitial = [5,9]
pathFinal = [15,24]

%Check if final x or y is equal to initial x or y within the bounds of 10%
if(pathInitial(1) >= pathFinal(1) - (0.10 * pathFinal(1)) && pathInitial(1) <= pathFinal(1) + (0.10 * pathFinal(1)))
    %Current Angle does not change

end
if(pathInitial(2) >= pathFinal(2) - (0.10 * pathFinal(2)) && pathInitial(2) <= pathFinal(2) + (0.10 * pathFinal(2)))
    %Current Angle does not change

end

%else
%Map out y value to finish path triangle
%(initial X, final Y)
%Use data to finish path triangle
%(initial X, finaly Y)
%(initial X, initial Y)
%(final X, final Y)
mappedVector = [pathInitial(1),pathFinal(2)];

%Get distance from initial vector to final vector
dInitial_Final = sqrt(power(pathFinal(1) - pathInitial(1),2) + power(pathFinal(2) - pathInitial(2),2));
%Get distance from initial vector to mapped vector
dInitial_Mapped = sqrt(power(mappedVector(1) - pathInitial(1),2) + power(mappedVector(2) - pathInitial(2),2));
%Get distance from mapped vector to final vector
dMapped_Final = sqrt(power(pathFinal(1) - mappedVector(1),2) + power(pathFinal(2) - mappedVector(2),2));
%Get angle A = cos(A) = c^2 + a^2 - b^2 / 2*c*a
b_ang = acosd(power(dInitial_Mapped,2) + power(dMapped_Final,2) - power(dInitial_Final,2) / 2 * dInitial_Mapped * dInitial_Final);
Angle = 180 - 90 - b_ang

if Angle < -45
    %Turn left

else if Angle > 45
    %Turn right

else if Angle > -45 && Angle < 45
    %Maintain direction

end

%
