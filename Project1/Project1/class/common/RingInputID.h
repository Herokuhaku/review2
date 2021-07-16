#pragma once

#include <vector>
#include <array>
#include <string>
#include "../input/inputID.h"

struct RingInputID
{
	RingInputID(int maxcount) {
		ringvec_.resize(maxcount);
		for (auto& ring : ringvec_) {
			ring.first = InputID::Max;
			ring.second = 0.0;
		}
		//ringvec_.fill(InputID::Max); 
		length_ = static_cast<int>(ringvec_.size());
	};
	~RingInputID() {};
	
	std::pair<InputID, double>& operator [](int count){
		if (count % length_ >= 0) {
			return ringvec_[count % length_];
		}
		else {
			int abs_ = length_ - abs(count) % 60;
			return ringvec_[abs_];
		}
	};
	
	void ClearRing(void) {
		for (auto& ring : ringvec_) {
			ring.first = InputID::Max;
			ring.second = 0.0;
		}
	};

	std::vector<std::pair<InputID, double>>& GetRing(void) {
		return ringvec_;
	};

	int size(void) {
		return static_cast<int>(ringvec_.size());
	};
private:
	std::vector<std::pair<InputID,double>> ringvec_;
	int length_;
};
