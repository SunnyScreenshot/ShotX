

@echo off
set windeployqt="D:\qt\Qt5.7.1_MSVC2013\5.7\msvc2013\bin\windeployqt.exe"

set myissue="demo.exe"


echo ��ǰwindeployqt·����: %windeployqt%


echo --------------------------------------
echo --------------------------------------
echo ������ȷ: 
echo �رյ�ǰ�ű������޸����е�Qt·����
echo --------------------------------------
echo ��·����ȷ:
pause
echo --------------------------------------
echo --------------------------------------

%windeployqt% %myissue%

pause