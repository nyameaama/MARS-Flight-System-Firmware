function [CLSa,CLSb] = findNeighborNodes(pointX,pointY,xrand,yrand)
    closestNode = []; 
    dists = []; 
    for i = 1: length(xrand)
        temp = findDistanceBetweenNodes(pointX,pointY,xrand(i),yrand(i)); 
        dists = [dists,temp]; 
    end
    closest = min(dists); 
    closestindX = find(dists == closest,1); 
    %Return the point
    CLSa = xrand(closestindX);  
    CLSb = yrand(closestindX);  
    
end