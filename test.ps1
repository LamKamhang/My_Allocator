cmake . -Bbuild -G"MinGW Makefiles" -DA=OFF -DB=OFF -DC=OFF -DD=OFF -DE=ON
cmake . -Bbuild -G"MinGW Makefiles" -DA=OFF -DB=OFF -DC=OFF -DD=OFF -DE=ON
cd build
mingw32-make
cd ..

$dir=Read-Host "where to store the test result"

if (!(Test-Path $dir))
{
	$null = New-Item -name $dir -ItemType Directory
}

echo testing...
$array=1..100
foreach ($n in $array)
{
	./build/MyAllocator.exe >> $dir/RESULT.txt
	echo ------------------------------------ >> $dir/RESULT.txt
}
echo finished!
echo "test result stored in $dir/RESULT.txt."