#ifndef SELECTION_GUI_H
#define SELECTION_GUI_H

#include <vector>

#include "Selection.h"


struct SelectionGui {
	SelectionGui(Selection& selection, bool p_center, bool p_corner);
	~SelectionGui();

	void draw();

	Selection& m_selection;

	bool m_center;
	bool m_corner;
};

#endif