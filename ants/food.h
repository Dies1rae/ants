#pragma once
#include "geo.h"

class food {
public:
	food() = default;
	food(const geo& coord, const size_t weigth) :weigth_(weigth), position_(coord) {};
	~food() = default;

	const size_t weigth() const {
		return this->weigth_;
	}

	const geo position() const {
		return this->position_;
	}

	size_t* mutable_weigth() {
		return &this->weigth_;
	}

	geo* mutable_position() {
		return &this->position_;
	}

	virtual void ant_pickup()  {
		if(this->weigth_ > 0) {
			--this->weigth_;
		}
	}

	virtual void ant_placedown()  {
		++this->weigth_;
	}

private:
	size_t weigth_ = 0;
	geo position_;
};

class ant_food : public food {
	ant_food() = default;
	ant_food(const geo& coord): position_(coord) {};
	~ant_food() = default;

	const size_t weigth() const {
		return this->weigth_;
	}

	const geo position() const {
		return this->position_;
	}
		
	geo* mutable_position() {
		return &this->position_;
	}

	virtual void ant_pickup() override {
		if (this->weigth_ == 0) {
			this->weigth_ = 1;
		}
	}

	virtual void ant_placedown() override {
		if (this->weigth_ == 1) {
			this->weigth_ = 0;
		}
	}

private:
	size_t weigth_ = 0;
	geo position_;
};