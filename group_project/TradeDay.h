#ifndef TradeDay_h
#define TradeDay_h

#include "pch.h"
#include "configure.h"
#include "DataTypes.h"
#include "utils.h"
#include <algorithm>
#include <vector>
#include <ostream>
#include <string>


class TradeDay
{
protected:
	const static std::vector<time_t> _trading_days;
	size_t _day_id;

public:
	TradeDay() = default;
	TradeDay(const time_t& time_str);
    static std::vector<time_t> set_time(const std::string& file_path);
    
	const TradeDay& move_forward(size_t N = 1);
	const TradeDay& move_backward(size_t N = 1);

	bool operator <(const TradeDay& rhs) const;
	bool operator >(const TradeDay& rhs) const;
	bool operator ==(const TradeDay& rhs) const;
	bool operator !=(const TradeDay& rhs) const;

	/*
	friend std::ostream& operator <<(std::ostream& ost, const TradeDay& td)
	{

		ost << _day_id << ": " << _trading_days[_day_id] << std::endl;
		return ost;

		ost << 0 << std::endl;
		return ost;
	}
	*/
};

#endif
