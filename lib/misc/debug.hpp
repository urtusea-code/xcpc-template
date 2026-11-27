#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;

void debug(int n, string k, const auto&... v) {
    stringstream in(k);
    cerr << "[" << n << "] ";
    ((getline(in >> ws, k, ','), cerr << k << " = " << v << "; "), ...);
    cerr << '\n';
}
#define DEBUG(...) debug(__LINE__, #__VA_ARGS__, __VA_ARGS__)
#define SPLIT(log) cerr << "\n" << log << "\n"
// #define DEBUG(...) void(0)
// #define SPLIT(log) void(0)

/*
    FE_INVALID	    1       浮点数产生 NaN
    FE_DIVBYZERO	4       浮点数除 0
    FE_OVERFLOW	    8       浮点数上溢
    FE_UNDERFLOW	16      浮点数下溢

    SIGSEGV         段错误
    SIGABRT         assert(...) 或者程序调用了 abort()
    SIGFPE          算数异常, 例如 /0 或 %0
    SIGILL          非法指令, 比如 CPU 不支持的指令集
    SIGBUS          内存访问错误
    SIGPIPE         交互题可能碰见, 读入端还没开始接收数据, 我们就直接输出
*/
int main() {
    feenableexcept(29);
    signal(SIGSEGV, [](int) { _Exit(0); } );
}