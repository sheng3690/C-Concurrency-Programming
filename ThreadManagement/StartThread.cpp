#include<iostream>
#include<thread>

class backgroud_task {
public:
	// 如果某个函数为const，那么其内部调用的函数也要是const
	void operator()() const {
		do_something();
		do_something_else();
	}
private:
	// 
	void do_something() const {
		std::cout << "do something\n" << std::endl;
	}
	void do_something_else() const {
		std::cout << "do something else\n" << std::endl;
	}
};

void do_something() {
	std::cout << "do something\n" << std::endl;
}
int main() {

	// 启动线程的方法1:创建thread对象时直接传入入口函数
	std::thread thread1(do_something);
	thread1.join();

	// 启动线程的方法2：创建thread对象时使用可调用类型构造
	backgroud_task f;
	std::thread thread2(f);
	thread2.join();
	// 错误的启动方法：创建thread对象时传入的是临时变量，而不是一个命名的可调用类型对象
	// 编译器回将其解析为函数声明，而不是类型对象的定义
	// 这里相当于声明了一个名为thread3的返回std::thread对象的函数，这个函数的参数是函数指针（指向没有参数并返回background_task对象的函数）
	// 因为函数声明中参数可以只指定类型而不指定名称
	std::thread thread3(backgroud_task());
	// 可以使用多组括号或者使用新同意的初始化语法解决这个问题
	std::thread thread4((backgroud_task()));
	thread4.join();
	std::thread thread5{ backgroud_task() };
	thread5.join();

	// 启动线程的方法3：lambda表达式
	std::thread thread6([] {
		do_something();
	});
	system("pause");
	return 0;
	


}