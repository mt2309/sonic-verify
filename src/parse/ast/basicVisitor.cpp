#include "parse/ast/basicVisitor.h"

namespace ast
{
	
BasicVisitor::BasicVisitor() {}

void BasicVisitor::visit(ast::RootNode* rootNode)
{
	std::cout << "Visiting Root " << rootNode->value << "\n";
}

void BasicVisitor::visit(ast::BodyNode* bodyNode)
{
	std::cout << "Visiting BodyNode " << bodyNode->value << "\n";		
}

void BasicVisitor::visit(ast::IntNode* intNode)
{
	std::cout << "Visiting IntNode " << intNode->val() << "\n";		
}

void BasicVisitor::visit(ast::FloatNode* floatNode)
{
	std::cout << "Visiting IntNode " << floatNode->val() << "\n";		
}

} // namespace ast