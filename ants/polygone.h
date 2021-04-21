#pragma once

#include "nest.h"

#include <vector>
#include <sstream>
#include <Windows.h>

class polygone {
public:

	const char border_sym = '0';
	const char ant_sym = '$';
	const char ground_sym = '.';
	const char ant_nest_sym = '@';

	polygone() = default;

	polygone(const size_t size_) {
		size_t actual_size = size_ + 2;
		geo nest_pos ((int)(actual_size / 2), (int)(actual_size / 2));

		ant_nest_ = new nest(nest_pos, 1);

		this->play_ground_.resize(actual_size);
		for (std::vector<char>& g : this->play_ground_) {
			g.resize(actual_size);
		}
	}

	polygone(const size_t size_, const size_t nest_size) {
		size_t actual_size = size_ + 2;
		geo nest_pos;
		if(size_ % 2 == 0){
			*nest_pos.mutable_x() = (int)(size_ / 2);
			*nest_pos.mutable_y() = (int)(size_ / 2);
		} else {
			*nest_pos.mutable_x() = (int)((size_ + 1) / 2);
			*nest_pos.mutable_y() = (int)((size_ + 1) / 2);
		}

		ant_nest_ = new nest(nest_pos, nest_size);

		this->play_ground_.resize(actual_size);
		for (std::vector<char>& g : this->play_ground_) {
			g.resize(actual_size);
		}
	}
	
	void mark_playground() {
		for (size_t x = 0; x < this->play_ground_.size(); x++) {
			for (size_t y = 0; y < this->play_ground_.size(); y++) {
				if (x == 0 || y == 0 || x == this->play_ground_.size() - 1 || y == this->play_ground_.size() - 1) {
					play_ground_[x][y] = border_sym;
				} else {
					play_ground_[x][y] = ground_sym;
				}
			}
		}
	}

	void mark_nest() {
		play_ground_[this->ant_nest_->position().x()][this->ant_nest_->position().y()] = ant_nest_sym;
	}

	void mark_ants() {
		for (const ant& a : this->ant_nest_->ants()) {
			play_ground_[a.position().x()][a.position().y()] = ant_sym;
		}
	}

	void display_playground(std::ostream& out) {
		this->mark_playground();
		this->mark_ants();
		this->mark_nest();

		for (size_t x = 0; x < this->play_ground_.size(); x++) {
			for (size_t y = 0; y < this->play_ground_.size(); y++) {
				out << this->play_ground_[x][y];
			}
			out << '\n';
		}
		out << '\n';
		Sleep(500);
		system("cls");
	}

	void display_size_debug_info(std::ostream& out) {
		out << "Field size: " << this->play_ground_.size() << "x" << this->play_ground_.size() << '\n';
		out << "Ant nest coord: " << this->ant_nest_->position().x() << ":" << this->ant_nest_->position().y() << '\n';
		out << "Ant nest size: " << this->ant_nest_->size() << " ants" << '\n';
		out << "Ants coord:" << '\n';
		for (size_t x = 0; x < this->ant_nest_->ants().size(); x++) {
			out << "Ant num " << x << " coord: ";
			out << this->ant_nest_->ants()[x].position().x() << ":" << this->ant_nest_->ants()[x].position().y() << '\n';
		}
		out << '\n';
	}

	void ants_turn() {
		this->ant_nest_->move();
	}

	void main_loop(std::ostream& out) {
		while (true) 	{
			this->display_playground(out);
			this->ant_nest_->move();
		}
	}

private:
	nest* ant_nest_;
	std::vector<std::vector<char>> play_ground_;
};

