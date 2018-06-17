cmake . -Bbuild -G"MinGW Makefiles" -DA=ON -DB=OFF -DC=OFF -DD=OFF
cmake . -Bbuild -G"MinGW Makefiles" -DA=ON -DB=OFF -DC=OFF -DD=OFF
cd build
mingw32-make
cd ..
build/MyAllocator.exe