export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./install/lib
gdb --args install/demo/tcc demo/test.c
