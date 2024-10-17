#include "Magnet.h"
#include "Manip.h"
#include <iostream>

using namespace Unigine;
using namespace Unigine::Math;

REGISTER_COMPONENT(Magnet)


void Magnet::Init() {

    status = ObjectStatus::out;

    trigger = checked_ptr_cast<WorldTrigger>(World::getNodeByName("WorldTrigger"));

    Visualizer::setEnabled(true);
    trigger->renderVisualizer();

    trigger->getEventEnter().connect(this, &Magnet::trigger_enter);
    trigger->getEventLeave().connect(this, &Magnet::trigger_leave);

}

void Magnet::Update() {

    std::cout << targetNode->getWorldRotation().x << " " << targetNode->getWorldRotation().y << " " << targetNode->getWorldRotation().z <<" " << targetNode->getWorldRotation().w << std::endl;

    trigger->renderVisualizer();

    if (!Input::isMouseButtonPressed(Input::MOUSE_BUTTON_LEFT) && status == ObjectStatus::connection) {

        dummy->addWorldChild(targetNode);

        targetNode->setWorldPosition(dummy->getWorldPosition());
        targetNode->setWorldRotation(dummy->getWorldRotation());
        targetNode->getObjectBodyRigid()->setEnabled(false);
        status = ObjectStatus::moving;
        Log::message("connection\n");
    }

    else if (status == ObjectStatus::moving) {

        targetNode->setWorldPosition(dummy->getWorldPosition());
        targetNode->setWorldRotation(dummy->getWorldRotation());
        Log::message("moving\n");
    }

    else if (status == ObjectStatus::out) {
        
        if (dummy->isChild(targetNode)) {
            dummy->removeChild(targetNode);
            targetNode->setWorldRotation(dummy->getWorldRotation());
        }
       targetNode->getObjectBodyRigid()->setEnabled(true);
       Log::message("out\n");

    }

}

void Magnet::trigger_enter(const NodePtr& node)
{

    if (node == targetNode.get()) {
        Log::message("TriggerEnter\n");
        status = ObjectStatus::connection;
    }
}


void Magnet::trigger_leave(const NodePtr& node)
{
    if (node == targetNode.get()) {
        Log::message("TriggerLeave\n");
        status = ObjectStatus::out;
    }
}