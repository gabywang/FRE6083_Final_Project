#ifndef EPSManager_h
#define EPSManager_h

#include "configure.h"
#include "TradeDay.h"
#include "DataTypes.h"
#include <string>

class EPSManager
{
protected:
	static EPSManager* _instance;
	
	Series<TickerInfo, false> _eps_diff_se;

	EPSManager(const std::string& file_path);
	EPSManager(const EPSManager& rhs) = delete;
	EPSManager& operator =(const EPSManager& rhs) = delete;

public:
	static EPSManager* get_instance(const std::string& file_path);

	Series<TickerInfo, false> get_summary() const;
	GroupResult get_group_result() const;

	~EPSManager();
};
#endif

