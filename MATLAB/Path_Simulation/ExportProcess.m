function ExportProcess(src,event,xrand,yrand,cbx)
    cbx_conv = cbx.Value;
    currentfolder = pwd;
    newFolder = "ShortestPath_output";
    if ~exist(newFolder, 'dir')
        mkdir(newFolder);
    end
    baseFileName = 'Path_output_generated.xlsx';
    fullFileName = fullfile(newFolder, baseFileName);
    XMap = reshape(xrand,[],1);
    YMap = reshape(yrand,[],1);
    %Description
    text = "This is the output of the Shortest Path matlab program.The first column holds the x values of the map and the second column holds the y values of the map.";
    writematrix(text,baseFileName,'Sheet','Sheet1','Range','D2');  
    %Get path
    path = []; 
    T = table(XMap,YMap);
    writetable(T,baseFileName);  
    movefile Path_output_generated.xlsx ShortestPath_output
    exportDescription(); 
end