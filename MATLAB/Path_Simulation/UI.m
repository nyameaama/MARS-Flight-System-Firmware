%UI
%UI
function UI()
    %initial point
   pointInitialX = 0;
   pointInitialY = 0;
   
   currentPosX = pointInitialX;
   currentPosY = pointInitialY;

   %end point
   endpointX = 0;
   endpointY = 0;

   exploredNodesX = [];
   exploredNodesY = [];


   %Create node map 
   xrand = (rand(1,500)*1000);
   yrand = (rand(1,500)*1000);

   f = uifigure('name','Path Simulation');
   set(f,'Position',[100 50 1000 700])
   
   gl = uigridlayout(f,[2,2]);
   gl.RowHeight = {'1x',30};
   gl.ColumnWidth = {'1x','2x'};
   
   p = uipanel(gl,'Title','Path Configuration');
   
   grid2 = uigridlayout(p,[3 2]);
   grid2.RowHeight = {22,22,22};
   grid2.ColumnWidth = {80,'1x'};
   
   %Path Density
   pDlabel = uilabel(grid2);
   pDlabel.HorizontalAlignment = 'right';
   pDlabel.Text = 'Swarm Density';

   promptPD = uieditfield(grid2);
   
   %Initial Point 
   pIXlabel = uilabel(grid2);
   pIXlabel.HorizontalAlignment = 'right';
   pIXlabel.Text = 'Initial Point (X)';

   promptIX = uieditfield(grid2);
   
   %Initial Point Y
   pIXlabel = uilabel(grid2);
   pIXlabel.HorizontalAlignment = 'right';
   pIXlabel.Text = 'Initial Point (Y)';

   promptIY = uieditfield(grid2);
   
   %Final Point X
   pFXlabel = uilabel(grid2);
   pFXlabel.HorizontalAlignment = 'right';
   pFXlabel.Text = 'Final Point (X)';

   promptFX = uieditfield(grid2);
   
   %Final Point Y
   pFYlabel = uilabel(grid2);
   pFYlabel.HorizontalAlignment = 'right';
   pFYlabel.Text = 'Final Point (Y)';

   promptFY = uieditfield(grid2);
  
   cbx = uicheckbox(grid2, 'Text','Show units in output',...
                 'Value', 0,...
                 'Position',[50 50 102 15],...
                 'FontSize',13,...
                 'WordWrap','on');
             
   cbx2 = uicheckbox(grid2, 'Text','Show nodes instead of path        (Will not trace route between the chosen nodes)',...
                 'Value', 0,...
                 'Position',[50 50 102 15],...
                 'FontSize',13,...
                 'WordWrap','on');
             
   cbx3 = uicheckbox(grid2, 'Text','Show visualizati-on in new window',...
                 'Value', 1,...
                 'Position',[50 50 102 15],...
                 'FontSize',13,...
                 'WordWrap','on');
    
   cbx4 = uicheckbox(grid2, 'Text','Optimize Performance (Computation will take a shorter time period)',...
                 'Value', 0,...
                 'Position',[50 50 102 15],...
                 'FontSize',13,...
                 'WordWrap','on');
             
   hlink = uihyperlink(grid2);
   hlink.Text = 'Learn more about path planning algorithms';
   hlink.WordWrap = 'on';
   %Motion planning From Wikipedia, the free encyclopedia
   hlink.URL = 'https://en.wikipedia.org/wiki/Motion_planning';
   
   pl = uiaxes(gl); 
   pl.Layout.Row = 1;
   pl.Layout.Column = 2;
   plot(pl,xrand,yrand,'.'); 
   title(pl,'Node Map');

   % Create and lay out button
   btn = uibutton(gl);
   btn.Layout.Row = 2;
   btn.Layout.Column = 1;
   btn.Text = 'Run Simulation';
   % Assign button callback function
   btn.ButtonPushedFcn = {@plotButtonPushed,currentPosX,currentPosY,xrand,yrand,exploredNodesX,exploredNodesY,promptIX,promptIY,promptFX,promptFY,promptPD,cbx,cbx2,cbx3,cbx4};
       
   % Create and lay out button
   btn2 = uibutton(gl);
   btn2.Layout.Row = 2;
   btn2.Layout.Column = 2;
   btn2.Text = 'Export Data to File';
   btn2.ButtonPushedFcn = {@ExportProcess,xrand,yrand,cbx};
   
   btn3 = uibutton(grid2);
   btn3.Text = 'View Program Description';
   btn3.ButtonPushedFcn = @Instructions_Description;
   
   Instructions_Description();%<SM:PDF_CALL>

end