@echo off

del *.h

REM ======generate head files============
rsc_string_maker.exe strings_all.txt ./

REM rsc_string_maker.exe strings_all_chn_new.txt ./


REM ======deal string id=================
DealStrId.exe


REM ======deal string content============
DealStrContent.exe


REM ======== ^_^ OK ^_^ =========

pause

@echo on