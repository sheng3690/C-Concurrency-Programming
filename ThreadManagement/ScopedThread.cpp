/*
	1. ��ThreadGuard�Ĳ�ͬ��ScopedThread�����½���һ���̣߳������ƶ����캯������ʼ���ý��̣�����ֱ�Ӵ�����ʱ�̱߳�����
	��ThreadGuard�����Ǳ������̵߳����ã��ڶ���������ʱ��ֻ�ܴ����������̱߳�����
	ThreadGuard�������������м���߳�joinable,ScopedThread�ڹ��캯���м�飬���ҵ��̲߳��ɼ��룬�׳��쳣
	���⣺
	1.Ϊʲô�ڹ��캯����Ҫ�����̷߳�joinable��
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
			std::cout << i << std::endl;  //1.Ǳ�ڷ�����������������
		}
	}
};
int main() {
	int local_var = 0;
	ScopedThread t(std::thread(func(local_var)));

	// do_something_in_current_thread();
	
}