#ifndef __TYPE_VISITOR_H__
#define __TYPE_VISITOR_H__

#include <vector>

#include "analysis/session/graph/iVisitor.h"

namespace analysis
{

class TypeVisitor : public analysis::IVisitor
{
public:
	TypeVisitor();

	~TypeVisitor() {}

	virtual void visit(graph::CueNode* cueNode);
	virtual void visit(graph::SyncNode* syncNode);
	virtual void visit(graph::CueNode* cueNode, std::string& type, std::vector<std::pair<std::string, std::string>> interactions);
	virtual void visit(graph::SyncNode* syncNode, std::string& type, std::vector<std::pair<std::string, std::string>> interactions);
};

} // namespace analysis

#endif // __TYPE_VISITOR_H__