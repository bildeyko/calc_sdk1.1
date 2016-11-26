@echo off
del *.msg

echo Y | del src\*.err > NUL
echo Y | del src\*.lst > NUL
echo Y | del src\*.obj > NUL

echo Y | del lst\*.lst > NUL
echo Y | del bin\*.obj > NUL
echo Y | del bin\*.hex > NUL
echo Y | del bin\*.bin > NUL