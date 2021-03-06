#ifndef __INT_NODE_H__
#define __INT_NODE_H__

#include "parse/ast/nodes/visitableNode.h"

namespace ast
{

class IntNode : public ast::VisitableNode
{
private:
	int num;

protected:

public:
	IntNode(int num, int index, int parent, int line, int statement, int blkDepth);

	int val();
	void accept(analysis::PTrace* trace, ast::VTimeVisitor* v);
};

} // namespace ast

#endif // __INT_NODE_H__