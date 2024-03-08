if [ ! -d "build" ]; then
  # /usr/bin/rm build -rf
  /usr/bin/mkdir build
fi
(
  cd build
  # cmake .. -DCMAKE_BUILD_TYPE=Debug
  cmake .. -DCMAKE_BUILD_TYPE=Release
  make install -j$(nproc)
)
