#pragma once

#include "ant.h"

#include <vector>
#include <stdexcept>
#include <random>

class nest {
public:
	nest() = default;

	nest(const geo& position, const size_t size): position_(position) {
		this->nest_.resize(size);
		for (ant& a : this->nest_) {
			*a.mutable_position() = position;
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

	 void move() {
		 for (size_t a = 0; a < this->nest_.size(); a++) {
			rnd_ant_move(this->nest_[a]);
		 }
	 }

private:
	void rnd_ant_move(ant& ant) {
		std::random_device r;
		std::mt19937 edge(r());

		int low_x = ant.position().x() - 1;
		int hight_x = ant.position().x() + 1;
		int low_y = ant.position().y() - 1;
		int hight_y = ant.position().y() + 1;

		std::uniform_int_distribution<int> normal_dist_x(low_x, hight_x);
		std::uniform_int_distribution<int> normal_dist_y(low_y, hight_y);

		*ant.mutable_position()->mutable_x() = normal_dist_x(edge);
		*ant.mutable_position()->mutable_y() = normal_dist_y(edge);
	}

	geo position_;
	std::vector<ant> nest_;
};

