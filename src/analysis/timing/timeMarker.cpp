#include "analysis/timing/timeMarker.h"

namespace analysis
{

TimeMarker::TimeMarker()
{
	// given how the constructor works, null check should really be done here
	if (!(Builder::tree))
	{
		std::cout << "tree hasn't initialized properly" << "\n";
	}

	// set up the trace structure inside tree
	(Builder::tree)->setUpTrace();
	ast::VTimeVisitor* visitor = new ast::VTimeVisitor();

	traceFirstPass(Builder::tree, visitor, false);

	analysis::PTrace* trace = (Builder::tree)->trace();
	std::cout << "End VT: " << trace->totalVT() << "\n";
	std::cout << " ===  First Pass Results ===\n";
	for (int i = 0; i < trace->traceSize(); ++i)
	{
		std::cout << "Index " << i 
				<< " has VT " << trace->stats[i]->conVT
				<< ", Current total: " << trace->stats[i]->cumVT 
				<< " IN FUNC:: " << trace->stats[i]->isInFunc()
				<< "\n";
	}
	std::cout << " === =================== ===\n";

	std::cout << "''Functions Defined''\n";
	for (auto it = (Builder::tree)->trace()->defFuncs.begin(); 
			it != (Builder::tree)->trace()->defFuncs.end();
			++it)
	{
		std::cout << "Function: " << it->first << " " << it->second << "\n";
	}

	std::cout << "\n";

	// second pass - collect function VT
	resolveIfs(trace, visitor);
	trace->traceSecondPass();

	std::cout << " === Second Pass Results ===\n";
	for (int i = 0; i < trace->traceSize(); ++i)
	{
		std::cout << "Index " << i 
				<< " has VT " << trace->stats[i]->conVT
				<< ", Current total: " << trace->stats[i]->cumVT 
				<< " IN FUNC:: " << trace->stats[i]->isInFunc()
				<< "\n";
	}
	std::cout << " === =================== ===\n";
}

void TimeMarker::resolveIfs(analysis::PTrace* trace, ast::VTimeVisitor* visitor)
{
	for (int i = 0; i < trace->traceSize(); ++i)
	{
		if (trace->stats[i]->conVT == -2)
		{
			int index = trace->stats[i]->getIfIndex();
			indexes fill;
			ast::VisitableNode* node = Builder::tree->findNode(index);
			node->accept(visitor, fill);
			int baseSize = (Builder::tree)->size();

			ast::VisitableNode* trueNode  = Builder::tree->findNode(fill.trueIndex);
			ast::VisitableNode* falseNode = Builder::tree->findNode(fill.falseIndex);
			ast::NodeTree* trueTree  = new ast::NodeTree(trueNode, baseSize);
			ast::NodeTree* falseTree = new ast::NodeTree(falseNode, baseSize);

			analysis::PTrace* trueTrace  = trueTree->trace();
			analysis::PTrace* falseTrace = falseTree->trace();

			traceFirstPass(trueTree, visitor, true);
			traceFirstPass(falseTree, visitor, true);

			std::cout << "True\n";
			trueTrace->traceSecondPass();
			std::cout << "False\n";
			falseTrace->traceSecondPass();

			int trueVT  = trueTrace->stats[trueTrace->getLast()]->cumVT;
			int falseVT = falseTrace->stats[falseTrace->getLast()]->cumVT;


std::cout << " ===  True Pass Results ===\n";
	for (int i = 0; i < trueTrace->traceSize(); ++i)
	{
		std::cout << "Index " << i 
				<< " has VT " << trueTrace->stats[i]->conVT
				<< ", Current total: " << trueTrace->stats[i]->cumVT 
				<< " IN FUNC:: " << trueTrace->stats[i]->isInFunc()
				<< "\n";
	}
	std::cout << " === =================== ===\n";

	std::cout << " ===  False Pass Results ===\n";
	for (int i = 0; i < falseTrace->traceSize(); ++i)
	{
		std::cout << "Index " << i 
				<< " has VT " << falseTrace->stats[i]->conVT
				<< ", Current total: " << falseTrace->stats[i]->cumVT 
				<< " IN FUNC:: " << falseTrace->stats[i]->isInFunc()
				<< "\n";
	}
	std::cout << " === =================== ===\n";

std::cout << "true " << trueVT << " false " << falseVT << "\n";
			if (trueVT > falseVT)
			{
				trace->stats[i]->conVT = trueVT;
			}
			else
			{
				trace->stats[i]->conVT = falseVT;
			}

			trace->stats[i]->cumVT = trace->stats[i]->conVT;

			if (!trace->stats[i - 1]->isInFunc())
			{
				trace->stats[i]->cumVT += trace->stats[i - 1]->cumVT;
			}

			delete trueTree;
			delete falseTree;
		}
	}

	std::cout << "fourth slot " << trace->stats[4]->conVT << "\n";
}

void TimeMarker::traceFirstPass(ast::NodeTree* tree, ast::VTimeVisitor* visitor,
			bool inIf)
{
	bool flag = true;
	analysis::PTrace* trace = tree->trace();
	_it = new ast::TreeIterator(*tree, tree->root());

	ast::TreeIterator start = tree->begin();
	ast::TreeIterator end   = tree->end();
	// first pass - setup VTs
	for (ast::TreeIterator it = start; it != end; ++it)
	{
		trace->setLast((&(*it))->statement());
		(&(*it))->accept(trace, visitor);
		if (inIf)
		{
			// -3 for dead code as later updater won't process it
			(Builder::tree)->trace()->stats[(&(*it))->statement()]->conVT = -3;
			flag = false;
		}
	}
}

} // namespace analysis