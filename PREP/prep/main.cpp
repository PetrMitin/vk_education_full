#include <iostream>
int foo(int &z)



{
return z + 7;

}

int main()

{
const int x = 11;
int y;
y = foo(2);
std::cout << x + y;



return 0;
}
