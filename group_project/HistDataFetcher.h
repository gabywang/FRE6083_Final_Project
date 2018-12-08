#ifndef HistDataFetcher_h
#define HistDataFetcher_h

#include "DataTypes.h"
#include "TradeDay.h"

class HistDataFetcher
{
protected:
	HistDataFetcher();
	HistDataFetcher(const HistDataFetcher& dm);
	HistDataFetcher& operator =(const HistDataFetcher& rhs);
	void _parse(ParseResult* result, const std::string& raw_str);

public:
	static HistDataFetcher* get_instance()
	{
		static HistDataFetcher _instance;
		return &_instance;
	}

	PriceBuff get_ticker_price(const Ticker& tkr, const TradeDay& start, const TradeDay& end);

};

inline void HistDataFetcher::_parse(ParseResult* result, const std::string& raw_str)
{
	;
}

#endif
