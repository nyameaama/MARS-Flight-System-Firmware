function [CLSa,CLSb] = findNeighborNodesEXP(pointX,pointY,xrand,yrand,visitedArray,no_of_neighbors)
    closestNode = []; 
    dists = []; 
    recurred = 0;
    for i = 1: length(xrand)
        temp = findDistanceBetweenNodes(pointX,pointY,xrand(i),yrand(i)); 
        dists = [dists,temp]; 
    end
    %Find the closest distances and add to array
    closestList = [];
    for j = 1:no_of_neighbors
        Vals = sort(dists); 
        closestList = [closestList,Vals(j)]; 
    end
    %Fin the indexes of the closest distances and add to separate array
    closestListIndxs = [];
    for j = 1:no_of_neighbors
        indxs = find(dists == closestList(j),1);  
        closestListIndxs = [closestListIndxs,indxs]; 
    end
    returnedX = [];
    returnedY = [];
    for j = 1:length(closestList)
        if visitedArray(closestListIndxs(j)) ~= 1 %  
            returnedX = [returnedX,xrand(closestListIndxs(j))]; 
            returnedY = [returnedY,yrand(closestListIndxs(j))]; 
        end
    end
    if isempty(returnedX)%
        if no_of_neighbors > 10  
            CLSa = 0; 
            CLSb = 0; 
        else
            [val1,val2] = findNeighborNodesEXP(pointX,pointY,xrand,yrand,visitedArray,no_of_neighbors+1); 
            CLSa = val1; 
            CLSb = val2; 
        end
    else
        CLSa = returnedX;   
        CLSb = returnedY;   
    end
    
end