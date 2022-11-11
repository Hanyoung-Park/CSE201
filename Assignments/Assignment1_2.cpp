#include <iostream>
using namespace std;

float func2(float n)
{
    if(n==2) return 1;
    return func2(n-1)*n;
}

int main() {
    int i;
    for(i=2;i<10;i++) cout << "test case for n = " << i << ": " << func2(i) << endl;
    return 0;
}
