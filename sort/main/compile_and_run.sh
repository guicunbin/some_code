test_size=$1
echo " the param number $# "

## check the param number 
if [ $# -ne 1 ]
then
    echo "just  need 1 param !!!! ";  exit;
fi

## compile and run
g++ main.cpp --std=c++11  && ./a.out ${test_size}
