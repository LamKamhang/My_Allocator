cmake . -Bbuild -G"MinGW Makefiles" -DA=OFF -DB=OFF -DC=OFF -DD=OFF -DE=ON
cmake . -Bbuild -G"MinGW Makefiles" -DA=OFF -DB=OFF -DC=OFF -DD=OFF -DE=ON
cd build
mingw32-make
cd ..
build/MyAllocator.exe