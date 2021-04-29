#pragma once
#include "UI.h"
#include "Panel.h"

class SynthPanel : public Panel {
private:

public:
	SynthPanel(DAW* daw_ptr, UI* parent_ptr) : Panel(daw_ptr, parent_ptr) { };
	virtual void handleButtons(std::vector<int> pressedButtons);
};