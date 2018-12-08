#ifndef TradeDay_h
#define TradeDay_h

#include "pch.h"
#include <vector>
#include <ostream>

class TradeDay
{
protected:
	const static std::vector<time_t> _trading_days;

	size_t _day_id;

public:
	TradeDay() = default;
	TradeDay(const std::string& time_str);

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

inline TradeDay::TradeDay(const std::string& time_str) : _day_id(0) { }

inline const TradeDay& TradeDay::move_forward(size_t N)
{
	return *this;
}

inline const TradeDay& TradeDay::move_backward(size_t N)
{
	return *this;
}

/*
bool TradeDay::operator <(const TradeDay& rhs) const
{
	return true;
}

bool TradeDay::operator >(const TradeDay& rhs) const
{
	return true;
}

bool TradeDay::operator ==(const TradeDay& rhs) const
{
	return true;
}

bool TradeDay::operator !=(const TradeDay& rhs) const
{
	return true;
}
*/

#endif

