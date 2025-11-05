@echo off
echo " This file appends:"
echo ""
echo "    MODE CON COLS=80 LINES=50"
echo ""
echo " to the file: 'C:\AUTOEXEC.BAT'"
echo ""
echo "Press any key to continue, or CTRL-C to terminate."
echo ""

pause >NUL

echo "MODE CON COLS=80 LINES=50" >> C:\AUTOEXEC.BAT