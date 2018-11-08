
#include<iostream>
#include<thread>

struct func
{
	int& i;
	func(int& i_):i(i_){}
	void operator()() {
		for (unsigned j = 0; j < 100000; ++j) {
			std::cout << i << std::endl;  //1.潜在访问隐患：悬空引用
		}
	}
};

int main() {
	int local_var = 0;
	func my_func(local_var);
	// my_func对象内部变量i是local_var的引用，当main函数结束时local_var被销毁，i是悬空引用，但是程序不会崩溃
	// 原因是引用是用指针实现的，引用变量保存着被引用对象的地址，尽管local_var被销毁，但是地址上的值是没有变的，所以不会出错，但是还是要避免这种情况
	std::thread t(my_func);
	try {
		std::cout << "do_something_in_current_thread" << std::endl;
	}
	catch (...) {
		t.join();
		throw;
	}
	t.join();
	//t.detach(); 2.不等待线程结束
	system("pause");
	// 解决方法：使线程函数的功能齐全，将数据复制到线程中，而非复制到共享数据中。如果使用一个可调用对象作为线程函数，这个对象就会复制到线程中。

}