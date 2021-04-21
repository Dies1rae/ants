#pragma once

#include "geo.h"
#include "enzym.h"

#include <stack>

class ant {
public:
	ant() = default;

	explicit ant(const geo& coord_of_nest): position_(coord_of_nest) {
		this->track_.push({ 0, coord_of_nest });
	}

	
	const bool carry_on() const {
		return this->carry_on_;
	}
	const size_t speed() const {
		return this->speed_;
	}
	const geo position() const {
		return this->position_;
	}
	const std::stack<enzym> enzym_() const {
		return this->track_;
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
	std::stack<enzym>* mutable_enzym_() {
		return &this->track_;
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
	void set_position(const int x, const int y) {
		*this->position_.mutable_x() = x;
		*this->position_.mutable_y() = y;
	}

	void ant_base() {
		this->track_.push({0, this->position_});
	}

	void ant_move(const int coor_x, const int coor_y) {
		this->set_position(coor_x, coor_y);
		enzym tmp = this->track_.top().new_enzym(this->position());
		this->track_.push(tmp);
	}

private:
	bool carry_on_ = 0;
	size_t speed_ = 1;
	geo position_;
	std::stack<enzym> track_;
};

