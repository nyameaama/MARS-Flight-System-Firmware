function showPlotAS(checkboxValue,array)%<SM:PDF>%<SM:PDF_PARAM>
    if checkboxValue == 0 
        figure(2)
        plot(array);
    else %<SM:IF>
        figure(2)
        plot(array,'.'); 
    end
end