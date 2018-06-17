cmake . -Bbuild -G"MinGW Makefiles" -DA=OFF -DB=OFF -DC=OFF -DD=ON
cmake . -Bbuild -G"MinGW Makefiles" -DA=OFF -DB=OFF -DC=OFF -DD=ON
cd build
mingw32-make
cd ..
build/MyAllocator.exe