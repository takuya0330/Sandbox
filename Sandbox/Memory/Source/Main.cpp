#include <iostream>

#include "BlockAllocator.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(int, char**)
{
#if defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	BlockAllocator block;
	if (!block.Initialize(16, sizeof(int), 5))
		return -1;

	int* p[5] = { 0 };

	p[0] = new (block.Allocate()) int(0);
	p[1] = new (block.Allocate()) int(1);
	p[2] = new (block.Allocate()) int(2);

	std::cout << "address = " << p[0] << ", value = " << *p[0] << std::endl;
	std::cout << "address = " << p[1] << ", value = " << *p[1] << std::endl;
	std::cout << "address = " << p[2] << ", value = " << *p[2] << std::endl;

	block.Deallocate(p[1]);
	p[1] = nullptr;

	p[1] = new (block.Allocate()) int(3);
	p[3] = new (block.Allocate()) int(4);
	p[4] = new (block.Allocate()) int(5);

	std::cout << "address = " << p[1] << ", value = " << *p[1] << std::endl;
	std::cout << "address = " << p[3] << ", value = " << *p[3] << std::endl;
	std::cout << "address = " << p[4] << ", value = " << *p[4] << std::endl;

	// block.Deallocate(p[0]);
	block.Deallocate(p[1]);
	block.Deallocate(p[2]);
	// block.Deallocate(p[3]);
	block.Deallocate(p[4]);

	block.Finalize();

	return 0;
}
