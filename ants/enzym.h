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
	const geo position() const {
		return this->position_;
	}

	geo* mutable_position() {
		return &this->position_;
	}

	void set_position(const geo& coords) {
		this->position_ = coords;
	}

private:
	size_t weight_ = 0;
	geo position_;
};

