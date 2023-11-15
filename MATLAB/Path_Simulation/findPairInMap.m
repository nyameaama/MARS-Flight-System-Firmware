function found = findPairInMap(xVal,yVal,xrand,yrand)  
    trueX = 1;
    search1 = find(xrand == xVal);  
    if isempty(search1)
        trueX = 0;
    end
    search2= find(yrand == yVal);  
    if isempty(search2)
        trueX = 0;
    else
        if search1 ~= search2  
            trueX = 0;
        end
    end
    if trueX == 1  
        found = search1;
    else
         found = -1;
    end
end
