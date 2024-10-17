#pragma once
#include <Unigine.h>

using namespace Unigine;
using namespace Unigine::Math;

class Manip : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Manip, ComponentBase)
	COMPONENT_INIT(Init)
	COMPONENT_UPDATE(Update)
	PROP_PARAM(Float, grab_distance)

private:
	PlayerPtr player = Game::getPlayer();
	ObjectPtr getIntersection();
	vec4 lastSelectedColor;
	ObjectPtr lastSelected;

	void GrabIt(ObjectPtr object);
	void HoldIt(ObjectPtr object);
	void ThrowIt(ObjectPtr object);

	bool hold = false;

	ObjectPtr IntersectionObject;

	Vec3 delta_vec;
	Vec3 delta_coord;
	quat delta_rot;
	float delta;

protected:
	void Init();
	void Update();

};