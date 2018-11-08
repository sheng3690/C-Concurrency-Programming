#include<iostream>
#include<thread>
#include<string>

/* ���̺߳������ݲ�������std::thread���캯���еĿɵ��ö��󣬻�������һ��������
Ĭ�ϲ���Ҫ�������̶߳����ڴ��У�֮���ں���ִ�е�ʱ���ٴ��ݸ�����������ʹ������������ʽ��
Ҳ���������߳��н��з��ʣ���Ҫ���Ǿֲ����������⣬���Է��ķ����̡߳�

*/

void print(int i, std::string const& s) {
	for (int j = 0; j < i; j++) {
		std::cout << s << std::endl;
	}
}
// �龰1:��ָ��ֲ�������ָ�뵱���������ݸ��߳̿��ܻᵼ������ָ��
void scene1(int some_param) {
	char buffer[1024];
	sprintf_s(buffer, "%i", some_param);
	std::thread t(print, 100, buffer);
	t.detach();
}
// ���:�ڴ��ݵ�std::thread���캯��֮ǰ�ͽ�����ֵת��Ϊstd::string����
void scene1_v2(int some_param) {
	char buffer[1024];
	sprintf_s(buffer, "%i", some_param);
	std::thread t(print, 100, std::string(buffer));
	t.detach();
}

// �龰2��������ݸ��̵߳Ĳ����������ã����ܸ��¾ֲ�������ֵ��
// �龰3�����Դ���һ����Ա����ָ����Ϊ�̺߳��������ṩһ�����ʵĶ���ָ����Ϊ��һ������
int main() {
	scene1(1024); 
}