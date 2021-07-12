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
			ring = InputID::Max;
		}
		//ringvec_.fill(InputID::Max); 
		length_ = static_cast<int>(ringvec_.size());
	};
	~RingInputID() {};
	
	InputID& operator [](int count){
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
			ring = InputID::Max;
	}
	};

	std::vector<InputID>& GetRing(void) {
		return ringvec_;
	};
private:
	std::vector<InputID> ringvec_;
	int length_;
};
