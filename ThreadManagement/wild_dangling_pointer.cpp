#include<iostream>

int main() {
	int *p; // ָ��δ��ʼ������ʱ p ΪҰָ��
	int *pi = nullptr;
	//std::cout << *pi << std::endl;
	{
		int i = 6;
		pi = &i; // ��ʱ pi ָ��һ�������ĵ�ַ
		*pi = 8; // ok
	}
	// std::cout << *p << std::endl; ����ָ��ʱû�г�ʼ���������ó���
	std::cout << *pi << std::endl;
	*pi = 6; // ���� pi ָ��ı��� i �Ѿ����٣���ʱ pi ����������ָ��
	std::cout << *pi << std::endl;
	// free(pi); free֮����������ָ�룬���ﲻ�ܽ�����
	// std::cout << *pi << std::endl;
	system("pause");
	return 0;
}