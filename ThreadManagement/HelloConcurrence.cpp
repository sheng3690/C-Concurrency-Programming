#include<iostream>
#include<thread>//管理线程的函数和类的头文件

void hello() {
	std::cout << "hello,concurrence world\n";
}

int main() {
	// 每个线程都必须具有一个初始函数，新线程t拥有hello（）函数作为初始函数
	std::thread t(hello);
	// 等待新线程结束
	t.join();
}