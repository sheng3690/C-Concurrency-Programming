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
	/* ֱ�Ӷ�һ��������и�ֵ�Ϳ�����Σ�յģ���Ϊ����ܻ�Ū���Ѿ�������̡߳�
	�κγ��Կ������߸�ֵ�Ĳ������������������
	*/
	ThreadGaurd(ThreadGaurd const&) = delete;//ɾ���������캯������
	ThreadGaurd& operator=(ThreadGaurd const&) = delete;//ɾ����ֵ����
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
	func my_func(local_var);
	std::thread t(my_func);
	ThreadGaurd g(t);
	// do_something_in_current_thread();
	/*
		���߳̽������ֲ�����Ҫ�������١���ˣ�ThreadGaurd����g�ǵ�һ��
		�����ٵģ���ʱ����ThreadGaurd������������������������߳��Ƿ�
		joinable������ǣ���join�����ִ������� do_something_in_current_thread();
		�����쳣�����������Ȼ������
		Ϊ��ȷ���߳��ں���֮ǰ����������ʹ�á���Դ��ȡ����ʼ����ʽ����RAII����
		���һ����ThreadGaurd,������
		�������ȴ��̣߳����Է����̣߳��Ӷ������쳣��ȫ���⡣
		�����̺߳󣬿��Ա����쳣��ȫ���⣬��ʹ�߳����ں�̨���� ���������Ҳ��ȷ��std::terminate��std::thread��������ʱ�����á� 
	*/ 
}