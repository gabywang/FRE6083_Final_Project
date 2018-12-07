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

	Series<TradeDay> get_ticker_price(Ticker&& tkr, TradeDay start, TradeDay end);

	~HistDataFetcher();
};

inline void HistDataFetcher::_parse(ParseResult* result, const std::string& raw_str)
{
	;
}

#endif
