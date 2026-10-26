binary=build/test_bonus

make clean; make $binary

if [[ ! -a $binary ]]; then
    echo "FAIL: $binary not made"
    echo "SCORE: 0/1"
    exit -1
fi
score=0


for (( i = 0; i < 1; i++ )); do
    echo "./build/test_bonus $i"
    ./build/test_bonus $i > /dev/null
    if [ "$?" -eq 2 ]; then
    ((score+=1))
    fi
done


echo "SCORE: $score/1"
