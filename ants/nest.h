#pragma once

#include "ant.h"

#include <vector>
#include <stdexcept>

class nest {
public:
	nest() = default;

	nest(const geo& position, const size_t size, const std::vector<std::vector<char>>& play_ground): position_(position), play_ground_(play_ground){
		for(size_t ptr = 0; ptr < size; ptr++) {
			ant tmp_ant(position, play_ground);
			this->nest_.push_back(tmp_ant);
		}
	}

	~nest(){
		for (size_t ptr = 0; ptr < this->nest_.size(); ptr++) {
			this->nest_[ptr].~ant();
		}
	}

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

	 void ant_nest_playground_init(const std::vector<std::vector<char>>& play_ground) {
		 this->play_ground_ = play_ground;
	 }

	 void move() {
		 for (size_t a = 0; a < this->nest_.size(); a++) {
			 this->nest_[a].ant_nest_playground_init(this->play_ground_);
			 this->nest_[a].rnd_ant_move();
		 }
	 }

private:
	geo position_;
	std::vector<ant> nest_;
	std::vector<std::vector<char>> play_ground_;
};

