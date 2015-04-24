#include "analysis/timing/timeMarker.h"

TimeMarker::TimeMarker()
{
	// given how the constructor works, null check should really be done here
	if (!(Builder::tree))
	{
		std::cout << "tree hasn't initialized properly" << "\n";
	}

	_it = new ast::TreeIterator(*(Builder::tree), (Builder::tree)->root());

	ast::TreeIterator start = Builder::tree->begin();
	ast::TreeIterator end   = Builder::tree->end();

	for (ast::TreeIterator it = start; it != end; ++it)
	{
		std::cout << (*it).value << "\n";
	}

	std::cout << "OUT OF LOOP" << "\n";

	// std::cout << (start != end) << "\n";

	// std::cout << (*start).value << "\n";

	// start++;

	// std::cout << (*start).value << "\n";

	// std::cout << Builder::tree->root()->value << "\n";
	// std::cout << Builder::tree->begin() << "\n";	

}