#include<iostream>
#include<thread>//�����̵߳ĺ��������ͷ�ļ�

void hello() {
	std::cout << "hello,concurrence world\n";
}

int main() {
	// ÿ���̶߳��������һ����ʼ���������߳�tӵ��hello����������Ϊ��ʼ����
	std::thread t(hello);
	// �ȴ����߳̽���
	t.join();
}