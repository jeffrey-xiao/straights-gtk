#include "Command.h"
#include "StraightsGuiComponent.h"

StraightsGuiComponent::StraightsGuiComponent(StraightsGuiComponent *parent): parent_(parent) {}

void StraightsGuiComponent::executeCommand(Command command) {
  this->parent_->executeCommand(command);
}
