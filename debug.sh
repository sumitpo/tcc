export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./release/lib
gdb --args release/demo/tcc demo/test.c
