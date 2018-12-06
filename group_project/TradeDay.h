#ifndef TradeDay_h
#define TradeDay_h
#include "pch.h"
#include <vector>

class TradeDay
{
protected:
	const static std::vector<time_t> _trading_days;

	size_t _day_id;

public:
	const TradeDay& move_forward(size_t N = 1);
	const TradeDay& move_backward(size_t N = 1);
	
	bool operator <(const TradeDay& rhs) const;
	bool operator >(const TradeDay& rhs) const;
	bool operator ==(const TradeDay& rhs) const;
	bool operator !=(const TradeDay& rhs) const;
};

inline const TradeDay& TradeDay::move_forward(size_t N = 1)
{
	;
}

inline const TradeDay& TradeDay::move_backward(size_t N = 1)
{
	;
}

bool TradeDay::operator <(const TradeDay& rhs) const
{

}

bool TradeDay::operator >(const TradeDay& rhs) const
{

}

bool TradeDay::operator ==(const TradeDay& rhs) const
{

}

bool TradeDay::operator !=(const TradeDay& rhs) const
{

}
#endif

