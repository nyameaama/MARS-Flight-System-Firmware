function result = findDistanceBetweenNodes(currentPosX,currentPosY,filteredX,filteredY) 
      %Use pythagoras to find distance between nodes
     dist = [];
     pythagoras = sqrt(power((filteredX - currentPosX),2) + power((filteredY - currentPosY),2));  
     if pythagoras ~= 0   
         dist = [dist,pythagoras];
     end
    result = dist;
end