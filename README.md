Client/Server keylogger program in C++ 17.

- Client runs on Windows and the server on Unix (Linux/macOs).
- The client and server connects through network :
	+ Data is serialized and deserialized using Boost.Serialization
	+ Data is sent asynchronously with Boost.ASIO
- The Server then store this data in a mongo database for further exploitation.
- gTest is used for testing the serialization and deserialization of objects, using Type-Parameterized Tests.

To build the server, on UNIX systems :
\
```
cd Spider
cmake .
make install
cd bin
./server 	// for the server program
./common_test 	// for gtests of serialization
./server_test	// for integration tests of server (not yet implemented)
```

To build the client, on Windows:
Be sure to have Boost 1.65.1 installed and static libraries compiled for cmake's find_package() to work.
Add those environment variables :
For Boost : 
- `BOOST_INCLUDEDIR PATH\boost_1_65_1` 
- `BOOST_LIBRARYDIR PATH\boost_1_65_1\stage\lib` 
- `BOOST_ROOT PATH   PATH\boost_1_65_1\boost` 
` 
 
For Mongo C++ Drivers : 
- `LIBMONGO_CXX_DIR PATH\mongo-cxx-drive\lib\cmake` 
- `LIBBSON_CXX_DIR PATH\mongo-cxx-drive\lib\cmake`

```
cd Spider
cmake .
make install
cd bin
./server
./client
```