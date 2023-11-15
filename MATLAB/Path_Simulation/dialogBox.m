function error = dialogBox() 
    errorMsg = 'Please make sure that any inputs follow these requirements - Input is less than the input Path Density - Input node coordinates greater than zero - Input Path Density is less than 1000';
    h = msgbox(errorMsg,"Error","error");
end