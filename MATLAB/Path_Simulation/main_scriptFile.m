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
% -------------------------------------------
%{
Program Number: 
Program Purpose: Path Simulation
 
Created By: Nyameaama Gambrah 
Created On: 24, 02, 2022
Last Modified On: 27, 03, 2022

Credit to: Nyameaama Gambrah

This application takes input through a GUI to select two nodes. 
(An origin and a destination). The shortest path is then calculated
through the nodes and a visualization is outputted.

SOURCES USED
- https://www.mathworks.com/help/matlab/ref/uicontrol.html
- https://www.mathworks.com/help/matlab/ref/uifigure.html
- https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
- https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
- http://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html

%}

%Maintenance Functions
clc 
clear
close all

%Main Function Call
UI();