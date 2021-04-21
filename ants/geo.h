#pragma once

#include <algorithm>

class geo {
public:
	geo() = default;

	explicit geo(const int x, const int y): x_(x), y_(y) {}

	geo(const geo& position): x_(position.x_), y_(position.y_){}
	geo(geo&& position) noexcept {
		std::swap(this->x_, position.x_);
		std::swap(this->y_, position.y_);
	}

	const int x() const {
		return this->x_;
	}
	const int y() const {
		return this->y_;
	}

	int* mutable_x() {
		return &this->x_;
	}
	int* mutable_y() {
		return &this->y_;
	}

	void set_x(const int x) {
		this->x_ = x;
	}
	void set_y(const int y) {
		this->y_ = y;
	}

	geo& operator=(const geo& coords) {
		this->x_ = coords.x_;
		this->y_ = coords.y_;
		return *this;
	}

	geo& operator=(geo&& coords) noexcept {
		std::swap(this->x_, coords.x_);
		std::swap(this->y_, coords.y_);
		return *this;
	}

private:
	int x_ = 0;
	int y_ = 0;
};

