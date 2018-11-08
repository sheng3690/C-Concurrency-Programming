/*
	ʵ��ԭ�����а�std::accumulate��������ͣ�
	���⣺
	1. ΪʲôҪ�½�һ��accumulate_block�ķº�����
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
	unsigned long const max_threads = (min_per_thread + length - 1) / min_per_thread; //��֤Ԫ��������1-25ʱ����25�õ�����1
	unsigned long const hardware_threads = std::thread::hardware_concurrency();
	unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	unsigned long const block_size = length / num_threads; //�˴��ᵼ�»���ʣ���Ԫ��Ϊ�γ�block�������Ƿ��1
	std::vector<T> results(num_threads);//�洢ÿ��block�Ľ��,��ʼֵӦ��Ϊ0
	std::vector<std::thread> threads(num_threads - 1); // �������߳��������num_threads��һ������Ϊ������֮ǰ�Ѿ�����һ���̣߳����̣߳�
	Iterator block_start = first;
	for (unsigned i = 0; i < (num_threads - 1); i++) {
		Iterator block_end = block_start;
		std::advance(block_end, block_size);
		threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));//���̺߳����������ò��ܱ�֤���ݵĹ���
		block_start = block_end;
	}
	accumulate_block<Iterator, T>() (block_start, last, results[num_threads - 1]);
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	return std::accumulate(results.begin(), results.end(), init);
}