#include<iostream>
#include<thread>

void fun_1() {
	std::cout << "fun_1()" << std::endl;
}

void fun_2() {
	std::cout << "fun_2()" << std::endl;
}
// 所有权在一个函数内转移
int main() {
	std::thread t1(fun_1); // t1是joianble的
	std::thread t2 = std::move(t1); // t1的所有权转交给了t2,t1变成非joinable，t2本身是非joinable的，t1将所有权转移后，变成了joinable
	t1 = std::thread(fun_2); // 启动了一个临时线程执行fun_2,将所有权交给非joinable的t1
	std::thread t3; //t3不是一个正在运行的线程，是非joinable
	t3 = std::move(t2); // 由于t3是非joinable的，所以可以将t2的所有权转移给t3,然后t3变成了joinable
	// t1 = std::move(t3); 出错，因为t1已经控制了一个线程，即joinable的，对joinable的线程移动赋值直接调用std::terminater()终止程序
	// t1,t3是joinable，要明确是join还是detach
	t1.join();
	t3.join();
	system("pause");
}

// 所有权在函数外转移

std::thread f() {
	;
}