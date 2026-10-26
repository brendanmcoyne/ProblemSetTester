binary=build/test

make clean; make

if [[ ! -a $binary ]]; then
    echo "FAIL: $binary not made"
    echo "SCORE: 0/13"
    exit -1
fi
score=0


for (( i = 0; i < 13; i++ )); do
    echo "Running test $i:"
    ./build/test $i 
    if [ "$?" -eq 1 ]; then
    ((score+=1))
    fi
done


echo "SCORE: $score/13"
