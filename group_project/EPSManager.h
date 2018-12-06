#ifndef EPSManager_h
#define EPSManager_h

#include "configure.h"
#include "TradeDay.h"
#include "DataTypes.h"
#include <string>

class EPSManager
{
protected:
	Series<TickerInfo> _eps_diff_series;

public:
	EPSManager();

	void load(const std::string& path = EPS_FILE);

	GroupResult get_group_result(int n) const;

	~EPSManager();
};

//ʹ��ָ��λ�õ�excel����ʼ��_eps_vector

#endif

