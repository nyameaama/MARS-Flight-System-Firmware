function [updatedXrand,updatedYrand] = addInitialAndEndpoint(promptIX,promptIY,promptFX,promptFY,xrand,yrand)
    %If initial and endpoint nodes arent in current map, add
    %Search for initial and endpoints
    tempX = xrand; 
    tempY = yrand; 
    initX = find(xrand == promptIX,1);   
    if(isempty(initX) == 1)   
        %Add to node map 
        tempX = [tempX,promptIX];  
    end
    initY = find(yrand == promptIY,1);   
    if(isempty(initY) == 1)   
        %Add to node map
        tempY = [tempY,promptIY];  
    end
    endX = find(xrand == promptFX,1);    
    if(isempty(endX) == 1)   
        %Add to node map
        tempX = [tempX,promptFX];  
    end
    endY = find(yrand == promptFY,1);   
    if(isempty(endY) == 1)  
        %Add to node map
        tempY = [tempY,promptFY];  
    end
    updatedXrand = tempX; 
    updatedYrand = tempY; 
end