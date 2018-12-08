#include "pch.h"
#include "TradeDay.h"
#include "utils.h"
#include <vector>
#include <fstream>

TradeDay::TradeDay(const std::string& file_path) {
	std::ifstream file;
	file.open(file_path);
	if (!file.is_open()) throw new std::runtime_error("Cannot open file.");

	/* Need to modify to import correctly.*/
	auto&& trading_day = read_col_from_csv<std::vector<time_t>(file, TRADING_START_ROW, TRADING_DAT_COL);

	file.close();

	const size_t len(trading_day.size());
	std::vector<time_t> _tmp(len);
	FOR_LOOP(0, i, len)
	{
		_tmp[i] = TradeDay(std::move(trading_day[i]));
	}

	/* Import trading day into vector with type time_t.*/
	_trading_days = std::move(std::vector<time_t>(_tmp));

}

//const std::vector<time_t> TradeDay::_trading_days = std::vector<time_t>(10);

TradeDay::TradeDay(const time_t & time_str) : _day_id(0) {
	//std::vector<time_t>::iterator itr;
	auto it = std::find(_trading_days.begin(), _trading_days.end(), time_str);
	if (it != _trading_days.end()) {
		_day_id = std::distance(_trading_days.begin(), it);
	}
	else { throw new std::invalid_argument("time_str not in range.");}
}

const TradeDay& TradeDay::move_forward(size_t N) {
	_day_id += N;
	return *this;
}

const TradeDay& TradeDay::move_backward(size_t N) {
	_day_id -= N;
	return *this;
}

bool TradeDay::operator <(const TradeDay& rhs) const {
	return (_day_id < rhs._day_id);
}

bool TradeDay::operator >(const TradeDay& rhs) const {
	return (_day_id > rhs._day_id);
}

bool TradeDay::operator ==(const TradeDay& rhs) const {
	return (_day_id == rhs._day_id);
}

bool TradeDay::operator !=(const TradeDay& rhs) const {
	return (_day_id != rhs._day_id);
}
