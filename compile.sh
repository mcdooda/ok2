mkdir -p Debug
cd Debug
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
make
cd ..

mkdir -p Release
cd Release
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
make
cd ..

