g++ -std=c++20 -o gen gen 
g++ -std=c++20 -o checker checker
g++ -std=c++20 -o $1 $1.cpp

while true; do
    ./gen > 1.in
    ./checker < 1.in > 1.ans
    ./checker < 1.in > 1.out
    if diff 1.out 1.ans; then
        echo ac
    else
        echo wa
        break
    fi
done