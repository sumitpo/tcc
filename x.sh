#!/usr/bin/env bash

system_name=$(uname)

build() {
  MKDIR=$(which mkdir)
  if [ ! -d "build" ]; then
    ${MKDIR} build
  fi
  (
    cd build || exit
    cmake .. -DCMAKE_BUILD_TYPE=$1
    if [ "$system_name" == "Linux" ]; then
      make install -j$(nproc)
    elif [ "$system_name" == "Darwin" ]; then
      make install -j$(sysctl -n hw.ncpu)
    else
      make install
    fi
  )
}

clean() {
  rm -rf build release
}

set_ld_path() {
  if [ "$system_name" == "Darwin" ]; then
    export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:./release/lib
  elif [ "$system_name" == "Linux" ]; then
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./release/lib
  else
    echo "unknown system"
  fi
}

run() {
  ./release/demo/tcc demo/test.c
}

debug() {
  gdb --args release/demo/tcc demo/test.c
}

main() {
  set_ld_path
  if [ -z "$1" ]; then
    build release
    run
    exit 0
  fi
  case "$1" in
    build)
      echo "start build process"
      build Release
      ;;
    run)
      echo "run the example"
      build Release
      run
      ;;
    debug)
      echo "debug the process"
      build Debug
      debug
      ;;
    clean)
      echo "clean the work"
      clean
      ;;
    *)
      echo "Invalid argument, use 'build', 'run', 'debug', 'clean'"
      ;;
  esac
}

main $@
