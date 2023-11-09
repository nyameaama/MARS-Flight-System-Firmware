function finalPath = plotButtonPushed(src,event,currentPosX,currentPosY,xrand,yrand,exploredNodesX,exploredNodesY,promptIX,promptIY,promptFX,promptFY,pathD,cbx,cbx2,cbx3,cbx4)%<SM:PDF>%<SM:PDF_PARAM>
%     Convert
    promptIX_conv = str2num(promptIX.Value);
    promptIY_conv = str2num(promptIY.Value);
    promptFX_conv = str2num(promptFX.Value);
    promptFY_conv = str2num(promptFY.Value);
    promptPathDensity = str2num(pathD.Value);
    cbx2_conv = cbx2.Value;
    cbx4_conv = cbx4.Value;
    
    %Verify edit fields have been populated, if not dialog box
    [ret1,ret2] = errorChecks(promptIX_conv,promptIY_conv,promptFX_conv,promptFY_conv,promptPathDensity,xrand);%<SM:PDF> 
    if ret1 == 0 || ret2 == 0      
        dialogBox();%<SM:PDF> 
        
    else    
        %Check if initial and final points are in map, if not append to map
        [xrandUPD,yrandUPD] = addInitialAndEndpoint(promptIX_conv,promptIY_conv,promptFX_conv,promptFY_conv,xrand,yrand);   
        %Use checkbox input to determine algorithm to be used 
        if cbx4_conv == 0 
            [indX,indY] = Path2(xrandUPD,yrandUPD,promptIX_conv,promptIY_conv,promptFX_conv,promptFY_conv,cbx2_conv);  
        else 
            %Path finds the shortest route and returns vector with final path
            %points
            [distancesR,visitedNodesR,indexEndR] = Path(xrandUPD,yrandUPD,promptIX_conv,promptIY_conv,exploredNodesX,exploredNodesY,cbx2_conv);   
        end
    end 
end  