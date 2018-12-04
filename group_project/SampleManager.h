#ifndef SampleManager_h
#define SampleManager_h

#include "DataTypes.h"

class SampleManager
{
protected:
	const GroupResult&& _g_result;

public:
	SampleManager(const GroupResult&& gr); //�������ֵ������ô�죿

	GroupResult get_sample(int n) const;

	~SampleManager();
};

#endif
