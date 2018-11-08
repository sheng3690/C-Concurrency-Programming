#include<iostream>
#include<thread>

class backgroud_task {
public:
	// ���ĳ������Ϊconst����ô���ڲ����õĺ���ҲҪ��const
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

	// �����̵߳ķ���1:����thread����ʱֱ�Ӵ�����ں���
	std::thread thread1(do_something);
	thread1.join();

	// �����̵߳ķ���2������thread����ʱʹ�ÿɵ������͹���
	backgroud_task f;
	std::thread thread2(f);
	thread2.join();
	// �������������������thread����ʱ���������ʱ������������һ�������Ŀɵ������Ͷ���
	// �������ؽ������Ϊ�������������������Ͷ���Ķ���
	// �����൱��������һ����Ϊthread3�ķ���std::thread����ĺ�������������Ĳ����Ǻ���ָ�루ָ��û�в���������background_task����ĺ�����
	// ��Ϊ���������в�������ָֻ�����Ͷ���ָ������
	std::thread thread3(backgroud_task());
	// ����ʹ�ö������Ż���ʹ����ͬ��ĳ�ʼ���﷨����������
	std::thread thread4((backgroud_task()));
	thread4.join();
	std::thread thread5{ backgroud_task() };
	thread5.join();

	// �����̵߳ķ���3��lambda���ʽ
	std::thread thread6([] {
		do_something();
	});
	system("pause");
	return 0;
	


}