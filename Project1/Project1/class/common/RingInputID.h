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
	};
	~RingInputID() {};
	
	InputID& operator [](int count){
		return ringvec_[count % 60];
	};
	
	std::vector<InputID>& GetRing(void) {
		return ringvec_;
	};
private:
	std::vector<InputID> ringvec_;
};
