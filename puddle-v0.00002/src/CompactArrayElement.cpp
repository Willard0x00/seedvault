#include "CompactArrayElement.h"

CompactArrayElement::CompactArrayElement() :
	m_index ( -1 ),
	m_deleted ( false )
{}

int CompactArrayElement::get_index() const {
	return m_index;
}

void CompactArrayElement::set_index(int index) {
	m_deleted = false;
	m_index = index;
}

void CompactArrayElement::mark_deleted() {
	m_deleted = true;
}

bool CompactArrayElement::is_deleted() const {
	return m_deleted;
}