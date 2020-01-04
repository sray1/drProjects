implib MMGR_D.lib MMGR_D.def
copy MMGR_D.lib d:\drgraf\lib
del  MMGR_D.lib                 
copy MMGR_D.dll d:\drgraf\lib
del  MMGR_D.dll                    
dir d:\drgraf\lib\MMGR_D.*
pause
