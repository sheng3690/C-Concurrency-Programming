
#include<iostream>
#include<thread>

struct func
{
	int& i;
	func(int& i_):i(i_){}
	void operator()() {
		for (unsigned j = 0; j < 100000; ++j) {
			std::cout << i << std::endl;  //1.Ǳ�ڷ�����������������
		}
	}
};

int main() {
	int local_var = 0;
	func my_func(local_var);
	// my_func�����ڲ�����i��local_var�����ã���main��������ʱlocal_var�����٣�i���������ã����ǳ��򲻻����
	// ԭ������������ָ��ʵ�ֵģ����ñ��������ű����ö���ĵ�ַ������local_var�����٣����ǵ�ַ�ϵ�ֵ��û�б�ģ����Բ���������ǻ���Ҫ�����������
	std::thread t(my_func);
	try {
		std::cout << "do_something_in_current_thread" << std::endl;
	}
	catch (...) {
		t.join();
		throw;
	}
	t.join();
	//t.detach(); 2.���ȴ��߳̽���
	system("pause");
	// ���������ʹ�̺߳����Ĺ�����ȫ�������ݸ��Ƶ��߳��У����Ǹ��Ƶ����������С����ʹ��һ���ɵ��ö�����Ϊ�̺߳������������ͻḴ�Ƶ��߳��С�

}