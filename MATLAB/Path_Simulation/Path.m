function [distancesR,visitedNodesR,indexEndR] = Path(xrand,yrand,promptIX,promptIY,exploredNodesX,exploredNodesY,cbx2) 
    count = 1;
    expNodesXCopy = 0;
    expNodesYCopy = 0;
     % First, we initialize the algorithm as follows:
    % We set the starting node.
    startX = promptIX;
    startY = promptIY;
    % We set the distances between the starting node and all other cities to infinity, except for the distance between the starting node and itself, which we set to 0.
    distances(1:length(xrand)) = Inf; 
    visitedNodes(1:length(xrand)) = 0;
    
    % After that, we iteratively execute the following steps:
    % We choose the node with the smallest value as the “current node” and visit all of its neighboring nodes. As we visit each neighbor, we update their tentative distance from the starting node.
    % Once we visit all of the current node’s neighbors and update their distances, we mark the current node as “visited.” Marking a node as “visited” means that we’ve arrived at its final cost.
    % We go back to step one. The algorithm loops until it visits all the nodes in the graph. 
    % The algorithm loops until it visits all the nodes in the graph. 

    currentDistance = 0;
    nextNode = 0;
    currentPosX = promptIX;
    currentPosY = promptIY;

    indexEnd = 502;
    indxs = [];  
    while count <= length(xrand)%<SM:WHILE> %<SM:ROP>   
        % We choose the node with the smallest value as the “current node” and visit all of its neighboring nodes. As we visit each neighbor, we update their tentative distance from the starting node.
       mindistance = Inf;
        for h = 1:length(xrand)  
            this_dist = findDistanceBetweenNodes(currentPosX,currentPosY,xrand(h),yrand(h));
            if this_dist < mindistance & visitedNodes(h)~= 1   
                mindistance = this_dist;
                nextNode = h;
            end
        end
        distances(count) = mindistance;
        visitedNodes(nextNode) = 1;
        indxs = [indxs,nextNode];
        currentPosX = xrand(nextNode);
        currentPosY = yrand(nextNode);

        count = count + 1;  

    end
    showPlotAS(cbx2,indxs);
    %Return values
    distancesR = distances;
    visitedNodesR = visitedNodes;
    indexEndR = indxs;
end
