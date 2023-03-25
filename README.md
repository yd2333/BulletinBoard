
## file description
```server.h server.c``` server 
```utils.h utils.h``` common function that all the strategey will use (test needed)
```test_client.h``` temporary client


## make file
Run the following code for running distributed servers
```
gcc -pthread distributed_server.c -o server
gcc test_client.c -o client
```

## run file
port is 5000, 5001, 5002, 5003, 5004
```
./server 0
./server 1
./server 2
./server 3
./server 4

./client 127.0.0.1 <port> key value
```