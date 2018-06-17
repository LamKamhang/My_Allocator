cmake . -Bbuild -G"MinGW Makefiles" -DA=OFF -DB=OFF -DC=OFF -DD=OFF
cmake . -Bbuild -G"MinGW Makefiles" -DA=OFF -DB=OFF -DC=OFF -DD=OFF
cd build
mingw32-make
cd ..
build/MyAllocator.exe