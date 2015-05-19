#ifndef __SYNC_NODE_H__
#define __SYNC_NODE_H__

#include <string>

#include "analysis/session/graph/nodes/graphNode.h"

namespace analysis
{

class SyncNode : public GraphNode
{
public:
	SyncNode(int index, int line, std::string symbol);

	virtual void accept(TypeVisitor* v);
};

} // namespace analysis

#endif // __SYNC_NODE_H__