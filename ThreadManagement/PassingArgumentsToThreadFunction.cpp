#include<iostream>
#include<thread>
#include<string>

/* 向线程函数传递参数，向std::thread构造函数中的可调用对象，或函数传递一个参数。
默认参数要拷贝到线程独立内存中，之后在函数执行的时候再传递给函数本身，即使参数是引用形式，
也可以在新线程中进行访问，不要考虑局部变量的问题，可以放心分离线程。

*/

void print(int i, std::string const& s) {
	for (int j = 0; j < i; j++) {
		std::cout << s << std::endl;
	}
}
// 情景1:当指向局部变量的指针当作参数传递给线程可能会导致悬空指针
void scene1(int some_param) {
	char buffer[1024];
	sprintf_s(buffer, "%i", some_param);
	std::thread t(print, 100, buffer);
	t.detach();
}
// 解决:在传递倒std::thread构造函数之前就将字面值转化为std::string对象。
void scene1_v2(int some_param) {
	char buffer[1024];
	sprintf_s(buffer, "%i", some_param);
	std::thread t(print, 100, std::string(buffer));
	t.detach();
}

// 情景2：如果传递给线程的参数不是引用，不能更新局部变量的值。
// 情景3：可以传递一个成员函数指针作为线程函数，并提供一个合适的对象指针作为第一个参数
int main() {
	scene1(1024); 
}