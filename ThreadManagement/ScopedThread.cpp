/*
	1. 与ThreadGuard的不同：ScopedThread类中新建了一个线程，利用移动构造函数来初始化该进程，可以直接传入临时线程变量，
	而ThreadGuard类中是保存了线程的引用，在定义其对象的时候只能传入命名的线程变量。
	ThreadGuard是在析构函数中检查线程joinable,ScopedThread在构造函数中检查，并且当线程不可加入，抛出异常
	问题：
	1.为什么在构造函数中要考虑线程非joinable？
	2.explicit?
*/

#include<iostream>
#include<thread>

class ScopedThread {
	std::thread t;
public:
	explicit ScopedThread(std::thread t_) :t(std::move(t_)) {
		if (!t.joinable()) {
			throw std::logic_error("No thread");
		}
	}
	~ScopedThread() {
		t.join();
	}
	ScopedThread(ScopedThread const&) = delete;
	ScopedThread& operator=(ScopedThread const&)) = delete;
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
	ScopedThread t(std::thread(func(local_var)));

	// do_something_in_current_thread();
	
}