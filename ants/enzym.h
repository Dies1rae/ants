#pragma once

#include "geo.h"

class enzym {
public:
	enzym() {};
	enzym(const geo& pos): position_(pos) {};
	enzym(const size_t w, const geo& pos): weight_(w), position_(pos) {};

	enzym& new_enzym(const geo& pos) {
		enzym* tmp_enz = new enzym(++this->weight_, pos);
		return *tmp_enz;
	}

	const size_t weight() const {
		return this->weight_;
	}
	const bool food() const {
		return this->food_;
	}
	const geo position() const {
		return this->position_;
	}

	geo* mutable_position() {
		return &this->position_;
	}
	bool* mutable_food() {
		return &this->food_;
	}

	void set_position(const geo& coords) {
		this->position_ = coords;
	}

private:

	bool food_ = 0;
	size_t weight_ = 0;
	geo position_;
};

