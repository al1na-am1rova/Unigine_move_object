#include "Manip.h"
#include <iostream>


using namespace Unigine;
using namespace Unigine::Math;

REGISTER_COMPONENT(Manip)

void Manip::Init() {

	Input::setMouseHandle(Input::MOUSE_HANDLE_GRAB);

	if (!grab_distance) grab_distance = 10;
}

void Manip::Update() {

	if (!hold) {
		IntersectionObject = getIntersection();
	}
	if (Input::isMouseButtonPressed(Input::MOUSE_BUTTON_LEFT) && IntersectionObject && !hold) {
		GrabIt(IntersectionObject);
	}
	else if (Input::isMouseButtonPressed(Input::MOUSE_BUTTON_LEFT) && IntersectionObject && hold) {
		HoldIt(IntersectionObject);
	}
	else if (Input::isMouseButtonUp(Input::MOUSE_BUTTON_LEFT) && IntersectionObject && hold) {
		ThrowIt(IntersectionObject);
	}

}

ObjectPtr Manip::getIntersection() {

	Vec3 from = player->getCamera()->getPosition();
	Vec3 to = from + (player->getViewDirection()) * grab_distance;

	WorldIntersectionPtr wi = WorldIntersection::create();
	ObjectPtr IntersectionObject = World::getIntersection(from, to, 1, wi);

	if (lastSelected) {
		lastSelected->getMaterial(0)->setParameterFloat4("albedo_color", lastSelectedColor);
	}

	if (IntersectionObject) {
		delta_vec = wi->getPoint() - from;
		delta = Math::length(delta_vec);
		delta_coord = wi->getPoint() - IntersectionObject->getPosition();

		lastSelected = IntersectionObject;
		lastSelectedColor = IntersectionObject->getMaterial(0)->getParameterFloat4("albedo_color");
		IntersectionObject->getMaterial(0)->setParameterFloat4("albedo_color", vec4_white);
		Log::message("INTERSECTION\n");
		std::cout << IntersectionObject->getName() << std::endl;

	}

	else lastSelected = NULL;

	return IntersectionObject;
}

void Manip::GrabIt(ObjectPtr object) {

	//delta_rot = object->getTransform().getRotate() * Math::inverse(player->getTransform().getRotate());
	Log::message("GrabIt");
	std::cout << object->getName() << std::endl;
	hold = true;

}

void Manip::HoldIt(ObjectPtr object) {

	Log::message("HoldIt");
	std::cout << object->getName() << std::endl;
	//object->setTransform((mat4)rotate(delta_rot * player->getTransform().getRotate()));
	object->setPosition(player->getCamera()->getPosition() + player->getViewDirection() * delta - delta_coord);
}

void Manip::ThrowIt(ObjectPtr object) {
	
	Log::message("ThrowIt");
	std::cout << object->getName() << std::endl;
	hold = false;

}