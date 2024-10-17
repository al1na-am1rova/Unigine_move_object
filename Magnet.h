#pragma once
#include <Unigine.h>

using namespace Unigine;
using namespace Unigine::Math;

class Magnet : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Magnet, ComponentBase)
	COMPONENT_INIT(Init)
	COMPONENT_UPDATE(Update)
	PROP_PARAM(Node, targetNode)
	PROP_PARAM(Node, dummy)
	PROP_PARAM(Node, triggerNode)

private:
	enum class ObjectStatus { out, connection, moving};
	ObjectStatus status;
	WorldTriggerPtr trigger;
	PlayerPtr player = Game::getPlayer();
	void trigger_enter(const NodePtr& node);
	void trigger_leave(const NodePtr& node);


protected:
	void Init();
	void Update();

};