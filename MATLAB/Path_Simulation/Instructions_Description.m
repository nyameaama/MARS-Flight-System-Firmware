function Instructions_Description(src,event)%<SM:PDF>
        ms_g = imread('pic.png'); 
        instructions ='Program Description - This project takes input through a GUI to select two nodes. (An origin and a destination). The shortest path is then calculated through the nodes and a visualization is outputted. The  the map density (the number of nodes shown)is able to be adjusted by inputting a number between 1 - 1000. At the left region of the GUI window, there are text input fields in which the user will type in an initial point and an endpoint. The GUI pushbutton named "Run Simulation" will compute the shortest path and change the dot graph shown to a graph with a line through showing the shortest path through the nodes.'; 
        h = msgbox(instructions,'Shortest Path','custom',ms_g);
    
end

