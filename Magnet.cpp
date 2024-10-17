#include "Magnet.h"
#include "Manip.h"
#include <iostream>

using namespace Unigine;
using namespace Unigine::Math;

REGISTER_COMPONENT(Magnet)


void Magnet::Init() {

    trigger = checked_ptr_cast<WorldTrigger>(World::getNodeByName("WorldTrigger"));

    Visualizer::setEnabled(true);
    trigger->renderVisualizer();

    trigger->getEventEnter().connect(this, &Magnet::trigger_enter);
    trigger->getEventLeave().connect(this, &Magnet::trigger_leave);

}

void Magnet::Update() {

    trigger->renderVisualizer();

    if (!Input::isMouseButtonPressed(Input::MOUSE_BUTTON_LEFT) && in) {

        targetNode->setWorldPosition(dummy->getWorldPosition());
        targetNode->setWorldRotation(dummy->getWorldRotation());
        targetNode->setWorldParent(dummy);
        targetNode->getObjectBodyRigid()->setEnabled(false);
    }

    else if (in && targetNode -> getParent() == dummy.get()) {

        targetNode->setWorldPosition(dummy->getWorldPosition());
        targetNode->setWorldRotation(dummy->getWorldRotation());
    }

    else {

       targetNode->setWorldParent(NULL);
       targetNode->getObjectBodyRigid()->setEnabled(true);

    }

}

void Magnet::trigger_enter(const NodePtr& node)
{

    if (node == targetNode.get()) {
        Log::message("TriggerEnter\n");
        in = true;
    }
}


void Magnet::trigger_leave(const NodePtr& node)
{
    if (node == targetNode.get()) {
        Log::message("TriggerLeave\n");
        in = false;
    }
}