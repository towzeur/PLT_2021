

mkdir build 
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make -s -j4
cd ..
cd ..
copy lib\libxml2.dll bin\
