#pragma once

#include "geo.h"


class ant {
public:
	ant() = default;

	explicit ant(const geo& coord_of_nest): position_(coord_of_nest) {}

	
	const bool carry_on() const {
		return this->carry_on_;
	}
	const size_t speed() const {
		return this->speed_;
	}
	const geo position() const {
		return this->position_;
	}

	bool* mutable_carry_on() {
		return &this->carry_on_;
	}
	size_t* mutable_speed() {
		return &this->speed_;
	}
	geo* mutable_position() {
		return &this->position_;
	}

	void set_carry_on(bool i) {
		this->carry_on_ = i;
	}
	void set_speed(size_t v) {
		this->speed_ = v;
	}
	void set_position(const geo& coords) {
		this->position_ = coords;
	}
	void mutable_position(const int x, const int y) {
		*this->position_.mutable_x() = x;
		*this->position_.mutable_y() = y;
	}

private:
	bool carry_on_ = 0;
	size_t speed_ = 1;
	geo position_;
};

