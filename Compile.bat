@echo off
set name=Encode

gcc %name%.c -o %name%.exe
taskkill /f /im %name%.exe >> log
ping localhost -n 1 >> log
del log
start %name%.exe