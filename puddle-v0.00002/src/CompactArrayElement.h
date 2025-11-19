#ifndef COMPACT_ARRAY_ELEMENT_H
#define COMPACT_ARRAY_ELEMENT_H

class CompactArrayElement {
public:
	CompactArrayElement();

	int get_index() const;

	void set_index(int index);

	void mark_deleted();

	bool is_deleted() const;
private:
	int m_index;
	bool m_deleted;
};

#endif