#include<iostream>
#include<thread>

class ThreadGaurd
{
	std::thread& t;
public:
	explicit ThreadGaurd(std::thread& t_) :t(t_) {}
	~ThreadGaurd() {
		if (t.joinable()) {
			t.join();
		}
	}
	/* 直接对一个对象进行赋值和拷贝是危险的，因为这可能会弄丢已经加入的线程。
	任何尝试拷贝或者赋值的操作都会引发编译错误
	*/
	ThreadGaurd(ThreadGaurd const&) = delete;//删除拷贝构造函数声明
	ThreadGaurd& operator=(ThreadGaurd const&) = delete;//删除赋值操作
};

struct func
{
	int& i;
	func(int& i_) :i(i_) {}
	void operator()() {
		for (unsigned j = 0; j < 100000; ++j) {
			std::cout << i << std::endl;  //1.潜在访问隐患：悬空引用
		}
	}
};

int main() {
	int local_var = 0;
	func my_func(local_var);
	std::thread t(my_func);
	ThreadGaurd g(t);
	// do_something_in_current_thread();
	/*
		当线程结束，局部对象要逆序销毁。因此，ThreadGaurd对象g是第一个
		被销毁的，这时调用ThreadGaurd的析构函数，析构函数检查线程是否
		joinable，如果是，就join。这种处理即便是 do_something_in_current_thread();
		报出异常，这个销毁依然发生。
		为了确保线程在函数之前结束，可以使用”资源获取即初始化方式“（RAII），
		提高一个类ThreadGaurd,在析构
		如果不想等待线程，可以分离线程，从而避免异常安全问题。
		分离线程后，可以避免异常安全问题，即使线程仍在后台运行 ，分离操作也能确保std::terminate在std::thread对象销毁时被调用。 
	*/ 
}