function [indX,indY] = Path2(xrandUPD,yrandUPD,promptIX,promptIY,exploredNodesX,exploredNodesY,cbx2)%<SM:PDF_PARAM>
     % First, we initialize the algorithm as follows:
    % We set the starting node.
    startX = promptIX;
    startY = promptIY;
    % We set the distances between the starting node and all other cities to infinity, except for the distance between the starting node and itself, which we set to 0.
    distances(1:length(xrandUPD)) = Inf; 
    visitedNodes(1:length(xrandUPD)) = 0;
    nextNode = 0;
    currentPosX = promptIX;
    currentPosY = promptIY;
    followingNode = 0;
    
    indexEnd = 502;
    promptFX = exploredNodesX;
    promptFY = exploredNodesY;
    indxsX = []; 
    indxsY = [];
    count = 1;
    while count <= length(xrandUPD)  
        % We choose the node with the smallest value as the “current node” and visit all of its neighboring nodes. As we visit each neighbor, we update their tentative distance from the starting node.
        mindistance = Inf;
        for h = 1:length(xrandUPD) 
            this_dist = findDistanceBetweenNodes(currentPosX,currentPosY,xrandUPD(h),yrandUPD(h));
            if this_dist < mindistance & visitedNodes(h)~= 1   
                mindistance = this_dist;
                nextNode = h;
            end
        end
        [CLSa,CLSb] = findNeighborNodesEXP(xrandUPD(nextNode),yrandUPD(nextNode),xrandUPD,yrandUPD,visitedNodes,3);
        if CLSa == 0 %<SM:IF>   
            count = length(xrandUPD) + 1;
        else
            costs = [];
            for p = 1:length(CLSa) 
                %G is the distance between the current node and the start node.
                g = findDistanceBetweenNodes(CLSa(p),CLSb(p),startX,startY);
                %H is the heuristic — estimated distance from the current node to the end node.
                h = findDistanceBetweenNodes(CLSa(p),CLSb(p),promptFX,promptFY);
                %F is the total cost of the node.
                f = g + h;
                costs = [costs,f];
            end
            leastCost = min(costs);
            leastCostIndex = find(costs == leastCost,1);   
            loc = findPairInMap(CLSa(leastCostIndex),CLSb(leastCostIndex),xrandUPD,yrandUPD);
            distances(count) = mindistance;
            visitedNodes(loc) = 1;
            indxsX = [indxsX,xrandUPD(loc)];
            indxsY = [indxsY,yrandUPD(loc)];
            currentPosX = xrandUPD(loc);
            currentPosY = yrandUPD(loc);
            followingNode = find(xrandUPD == CLSa(leastCostIndex),1);   
            count = count + 1;
        end
          
    end
    showPlotAS(cbx2,indxsX);
    indX = indxsX; 
    indY = indxsY; 
end