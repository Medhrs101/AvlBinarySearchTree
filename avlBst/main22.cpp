#include <iostream>
using namespace std;

int fun(int* ptr)
{
	*ptr = *ptr + 10;
	return (*ptr);
}

int main(void)
{
	int val = 10;
	const int *ptr = &val;
	int *ptr1 = const_cast <int *>(ptr);
	fun(ptr1);
	cout << val;
	return 0;
}
