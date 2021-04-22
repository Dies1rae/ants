#pragma once

#include "ant.h"

#include <vector>
#include <stdexcept>

class nest {
public:
	nest() = default;

	nest(const geo& position, const size_t size): position_(position) {
		for(size_t ptr = 0; ptr < size; ptr++) {
			ant tmp_ant(position);
			this->nest_.push_back(tmp_ant);
		}
	}

	~nest() = default;

	const geo position() const {
		return this->position_;
	}
	const size_t size() const {
		return this->nest_.size();
	}

	const bool is_empty() const {
		return this->nest_.empty();
	}

	const ant ant_(const size_t num) const {
		if (num - 1 >= this->nest_.size()) {
			throw std::overflow_error("nest size error");
		}
		return this->nest_[num - 1];
	}

	const std::vector<ant> ants() const {
		return this->nest_;
	}

	ant* mutable_ant_(size_t num) {
		if (num - 1 >= this->nest_.size()) {
			throw std::overflow_error("nest size error");
		}
		return &this->nest_[num - 1];
	}

	 std::vector<ant>* mutable_ants() {
		return &this->nest_;
	 }

	 void move() {
		 for (size_t a = 0; a < this->nest_.size(); a++) {
			 this->nest_[a].rnd_ant_move();
		 }
	 }

private:
	geo position_;
	std::vector<ant> nest_;
};

