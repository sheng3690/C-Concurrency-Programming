/*
	���������������̣����ȴ��������
*/
#include<iostream>
#include<thread>
#include<vector>
#include<algorithm>

// �̺߳���
void thread_fun(unsigned i) {
	std::cout << "Thread " << i << "is executing" << std::endl;
}

int main() {
	std::vector<std::thread> threads;
	for (unsigned i = 0; i < 20; i++) {
		threads.push_back(std::thread(thread_fun, i));
	}
	std::for_each(threads.begin(), threads.end(), mem_fn(&std::thread::join));
	system("pause");
	return 0;
	//��������ˣ���Ϊ�����̹߳�ͬ���У���ӡ�Ķ�������
}