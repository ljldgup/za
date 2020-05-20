rpcgen test.x -a

# add operation in test_client.c test_server.c

make –f makefile.test

./test_server
./test_client 127.0.0.1