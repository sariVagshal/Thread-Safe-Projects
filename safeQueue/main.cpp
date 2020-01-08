#include "safeQueue.h"
#include <iostream>


int main()
{
	std::cout << "Hi!" << std::endl;
    
	SafeQueue<int> sf;
	sf.push(1);
	sf.push(2);
	sf.push(3);
	std::cout << "sf.pop(): " << sf.pop() << std::endl;
	std::cout << "sf.pop(): " << sf.pop() << std::endl;
	std::cout << "sf.pop(): " << sf.pop() << std::endl;
	std::cout << "sf.pop(): " << sf.pop() << std::endl;
	sf.push(4);
	sf.push(4);
	sf.push(4);
	sf.push(4);
	sf.push(4);
	std::cout << "sf.pop(): " << sf.pop() << std::endl;
	std::cout << "sf.pop(): " << sf.pop() << std::endl;
	std::cout << "sf.pop(): " << sf.pop() << std::endl;
	std::cout << "sf.pop(): " << sf.pop() << std::endl;

	return 0;
}






