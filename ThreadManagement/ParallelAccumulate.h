/*
	实现原生并行版std::accumulate（容器求和）
	问题：
	1. 为什么要新建一个accumulate_block的仿函数？
	2. 
*/
#include<thread>
#include<vector>
#include<algorithm>
#include<numeric>

template<typename Iterator,typename T>
struct accumulate_block {
	void operator()(Iterator first, Iterator last, T& result) {
		result = std::accumulate(first, last, result);
	}
};

template<typename Iterator,typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
	unsigned long const length = std::distance(first, last);
	if (!length)
		return init;
	unsigned long const min_per_thread = 25;
	unsigned long const max_threads = (min_per_thread + length - 1) / min_per_thread; //保证元素数量在1-25时除以25得到的是1
	unsigned long const hardware_threads = std::thread::hardware_concurrency();
	unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	unsigned long const block_size = length / num_threads; //此处会导致还有剩余的元素为形成block，考虑是否加1
	std::vector<T> results(num_threads);//存储每个block的结果,初始值应该为0
	std::vector<std::thread> threads(num_threads - 1); // 启动的线程数必须比num_threads少一个，因为在启动之前已经有了一个线程（主线程）
	Iterator block_start = first;
	for (unsigned i = 0; i < (num_threads - 1); i++) {
		Iterator block_end = block_start;
		std::advance(block_end, block_size);
		threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));//给线程函数传入引用才能保证数据的共享
		block_start = block_end;
	}
	accumulate_block<Iterator, T>() (block_start, last, results[num_threads - 1]);
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	return std::accumulate(results.begin(), results.end(), init);
}