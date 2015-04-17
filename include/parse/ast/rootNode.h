#ifndef __ROOT_NODE_H__
#define __ROOT_NODE_H__

#include "parse/ast/visitableNode.h"

namespace ast
{

class RootNode : public ast::VisitableNode
{
private:

protected:

public:
	RootNode();
	RootNode(std::string root);

	void accept(IVisitor v);
};

} // namespace ast

#endif // __ROOT_NODE_H__