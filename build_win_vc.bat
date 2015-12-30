@echo off

set CC=cl.exe

mkdir bin 2> NUL
mkdir obj 2> NUL

pushd obj

echo Building worm_test...
%CC% /nologo /I../libs /Fe../bin/worm_test.exe /FAcsu /W4 /WX /O2 /EHsc ../tests/worm_test.cpp
echo.

popd
