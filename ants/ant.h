#pragma once

#include "geo.h"
#include "enzym.h"
#include "food.h"

#include <vector>
#include <random>
#include <iostream>

class ant {
public:
	ant() = default;

	explicit ant(const geo& coord_of_nest, const std::vector<std::vector<char>> play_ground): position_(coord_of_nest) {
		enzym tmp_first(0, coord_of_nest);
		this->coord_nest_ = coord_of_nest;
		this->track_.push_back(tmp_first);
		this->play_ground_ = play_ground;
		this->food = nullptr;
		this->rnd_ant_move_direction();
	}
	
	~ant() = default;

	const bool carry_on() const {
		return this->food_carry_on_;
	}

	const bool walk_home() const {
		return this->walk_home_;
	}

	const size_t speed() const {
		return this->speed_;
	}

	const geo position() const {
		return this->position_;
	}

	const std::vector<enzym> enzym_() const {
		return this->track_;
	}

	bool* mutable_carry_on() {
		return &this->food_carry_on_;
	}

	bool* mutable_walk_home() {
		return &this->walk_home_;
	}

	size_t* mutable_speed() {
		return &this->speed_;
	}

	geo* mutable_position() {
		return &this->position_;
	}

	std::vector<enzym>* mutable_enzym_() {
		return &this->track_;
	}

	void set_carry_on(bool i) {
		this->food_carry_on_ = i;
	}

	void set_speed(size_t v) {
		this->speed_ = v;
	}

	void set_position(const geo& coords) {
		this->position_ = coords;
	}

	void set_position(const int x, const int y) {
		this->position_.set_x(x);
		this->position_.set_y(y);
	}

	void ant_nest_playground_init(const std::vector<std::vector<char>>& play_ground) {
		this->play_ground_ = play_ground;
	}

	void ant_base_init() {
		this->track_.push_back({0, this->position_});
		this->rnd_ant_move_direction();
	}

	void ant_move(const int coor_x, const int coor_y) {
		this->set_position(coor_x, coor_y);
		this->time_++;
		if(!this->walk_home_){
			enzym tmp = this->track_.back().new_enzym(this->position());
			this->track_.push_back(tmp);
		}
	}

	void check_enzym() {
		if (this->time_ == 100) {
			this->walk_home_ = 1;
		}
		else if (this->time_ >= 100 && this->position_.x() == this->coord_nest_.x() && this->position_.y() == this->coord_nest_.y()) {
			this->walk_home_ = 0;
			this->track_.clear();
			this->time_ = 0;
			enzym tmp_first(0, this->coord_nest_);
			this->track_.push_back(tmp_first);
		}
	}

	void rnd_ant_move() {
		int ant_next_step_x = 0;
		int ant_next_step_y = 0;
		this->check_enzym();
		if (this->walk_home_) {
			if (!this->track_.empty()) {
				enzym position = this->track_.back();
				ant_next_step_x = position.position().x();
				ant_next_step_y = position.position().y();
				this->track_.pop_back();
			}
		} else if (!this->walk_home_) {
			std::random_device r;
			std::mt19937 edge(r());
		
			int low_x = 0;
			int hight_x = 0;
			int low_y = 0;
			int hight_y = 0;

			if (this->direction_ == direction::NO) {
				low_x = this->position().x();
				hight_x = this->position().x() + 1;
				low_y = this->position().y() - 1;
				hight_y = this->position().y() + 1;
			} else if (this->direction_ == direction::SO) {
				low_x = this->position().x() - 1;
				hight_x = this->position().x();
				low_y = this->position().y() - 1;
				hight_y = this->position().y() + 1;
			} else if (this->direction_ == direction::EA) {
				low_x = this->position().x() - 1;
				hight_x = this->position().x() + 1;
				low_y = this->position().y();
				hight_y = this->position().y() + 1;
			} else if (this->direction_ == direction::WE) {
				low_x = this->position().x() - 1;
				hight_x = this->position().x() + 1;
				low_y = this->position().y() - 1;
				hight_y = this->position().y();
			}

			std::uniform_int_distribution<int> normal_dist_x(low_x, hight_x);
			std::uniform_int_distribution<int> normal_dist_y(low_y, hight_y);

			ant_next_step_x = normal_dist_x(edge);
			ant_next_step_y = normal_dist_y(edge);

			bool brakes = this->ant_eye(ant_next_step_x, ant_next_step_y);
			while (brakes) {
				this->rnd_ant_move_direction();
				ant_next_step_x = normal_dist_x(edge);
				ant_next_step_y = normal_dist_y(edge);
				brakes = this->ant_eye(ant_next_step_x, ant_next_step_y);
			}
		}
		this->ant_move(ant_next_step_x, ant_next_step_y);
	}

private:
	//NEED to ADD BRAIN and correct moves to enzym_food_buddies
	bool ant_eye(const int x_, const int y_) {
		for (size_t x = 0; x < this->play_ground_.size(); x++) {
			for (size_t y = 0; y < this->play_ground_.size(); y++) {
				if (x == x_ && y == y_) {
					if (this->play_ground_[x][y] == '0') {
						return true;
					}
				}
			}
		}
		return false;
	}

	void rnd_ant_move_direction() {
		std::random_device r;
		std::mt19937 edge(r());
		std::uniform_int_distribution<int> normal_dist_direct(0, 3);
		this->direction_ = (direction)normal_dist_direct(edge);
	}

	bool walk_home_ = 0;
	bool food_carry_on_ = 0;
	size_t time_ = 0;
	size_t speed_ = 1;
	ant_food* food;
	direction direction_;
	geo position_;
	geo coord_nest_;
	std::vector<enzym> track_;
	std::vector<std::vector<char>> play_ground_; //need to refactor(too much copies)
};

