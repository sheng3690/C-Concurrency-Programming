#include<iostream>
#include<thread>

void fun_1() {
	std::cout << "fun_1()" << std::endl;
}

void fun_2() {
	std::cout << "fun_2()" << std::endl;
}
// ����Ȩ��һ��������ת��
int main() {
	std::thread t1(fun_1); // t1��joianble��
	std::thread t2 = std::move(t1); // t1������Ȩת������t2,t1��ɷ�joinable��t2�����Ƿ�joinable�ģ�t1������Ȩת�ƺ󣬱����joinable
	t1 = std::thread(fun_2); // ������һ����ʱ�߳�ִ��fun_2,������Ȩ������joinable��t1
	std::thread t3; //t3����һ���������е��̣߳��Ƿ�joinable
	t3 = std::move(t2); // ����t3�Ƿ�joinable�ģ����Կ��Խ�t2������Ȩת�Ƹ�t3,Ȼ��t3�����joinable
	// t1 = std::move(t3); ������Ϊt1�Ѿ�������һ���̣߳���joinable�ģ���joinable���߳��ƶ���ֱֵ�ӵ���std::terminater()��ֹ����
	// t1,t3��joinable��Ҫ��ȷ��join����detach
	t1.join();
	t3.join();
	system("pause");
}

// ����Ȩ�ں�����ת��

std::thread f() {
	;
}