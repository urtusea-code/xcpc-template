g++ -std=c++20 -D_GLIBCXX_DEBUG -fsanitize=address,undefined -O2 -g \
    -o $1 $1.cpp && \
./$1.out < 1.in > 1.ans