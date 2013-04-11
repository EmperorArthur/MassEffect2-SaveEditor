set file1=%1%
set file2=%2%
SaveExtract.exe %file1% > %file1%.txt
SaveExtract.exe %file2% > %file2%.txt
diff %file1%.txt  %file2%.txt