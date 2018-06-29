cmake . -Bbuild -G"MinGW Makefiles" -DA=OFF -DB=OFF -DC=OFF -DD=OFF -DE=ON
cmake . -Bbuild -G"MinGW Makefiles" -DA=OFF -DB=OFF -DC=OFF -DD=OFF -DE=ON
cd build
mingw32-make
cd ..
echo testing...
$array=1..100
foreach ($n in $array)
{
	./build/MyAllocator.exe >> ./doc/RESULT3.txt
	echo ------------------------------------ >> ./doc/RESULT3.txt
}
echo finished!