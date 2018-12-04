#ifndef PlotManager_h
#define PlotManager_h

#include "DataTypes.h"

class PlotManager
{
protected:
	PlotManager();
	PlotManager(const PlotManager& rhs);
	PlotManager& operator =(const PlotManager& rhs);

public:
	static PlotManager* get_instance()
	{
		static PlotManager _instance;
		return &_instance;
	}

	void plot(const Series<int>&& ar_data);
	void show();

	~PlotManager();
};

#endif
