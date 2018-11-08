#include<iostream>

int main() {
	int *p; // 指针未初始化，此时 p 为野指针
	int *pi = nullptr;
	//std::cout << *pi << std::endl;
	{
		int i = 6;
		pi = &i; // 此时 pi 指向一个正常的地址
		*pi = 8; // ok
	}
	// std::cout << *p << std::endl; 定义指针时没有初始化，解引用出错
	std::cout << *pi << std::endl;
	*pi = 6; // 由于 pi 指向的变量 i 已经销毁，此时 pi 即成了悬空指针
	std::cout << *pi << std::endl;
	// free(pi); free之后变成了悬空指针，这里不能解引用
	// std::cout << *pi << std::endl;
	system("pause");
	return 0;
}