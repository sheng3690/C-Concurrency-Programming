/*
	利用容器量产进程，并等待他们完成
*/
#include<iostream>
#include<thread>
#include<vector>
#include<algorithm>

// 线程函数
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
	//结果乱套了，因为各个线程共同进行，打印的东西很乱
}