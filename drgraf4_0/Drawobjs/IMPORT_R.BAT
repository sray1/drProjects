implib Draw_D.lib Draw_D.def
copy Draw_D.lib d:\drgraf\lib
del  Draw_D.lib                   
copy Draw_D.dll d:\drgraf\lib
del  Draw_D.dll                    
dir d:\drgraf\lib\draw_d.*
pause
