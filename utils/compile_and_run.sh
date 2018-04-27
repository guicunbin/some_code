 #g++ test_utils.cpp --std=c++11
 g++ test_utils.cpp --std=c++11 -lcblas `pkg-config --cflags --libs opencv`  && ./a.out
 #g++ test_utils.cpp --std=c++11 -lcblas
