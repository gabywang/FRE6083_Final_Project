#include "pch.h"
#include "TradeDay.h"
#include "utils.h"
#include "DataTypes.h"
#include "configure.h"
#include <vector>
#include <fstream>

std::vector<time_t> TradeDay::set_time(const std::string& file_path) {
    std::ifstream file;
    file.open(file_path);
    if (!file.is_open()) throw new std::runtime_error("Cannot open file.");
    std::vector<time_t> trading_days = read_col_from_csv<std::vector<time_t>, time_t>(file, TRADING_START_ROW, TRADING_DAT_COL);
    file.close();
    return trading_days;
}

//const std::vector<time_t> TradeDay::_trading_days = std::vector<time_t>(10);
const std::vector<time_t> TradeDay::_trading_days = TradeDay::set_time(".\fake_time.csv");

TradeDay::TradeDay(const time_t & time_str) : _day_id(0) {
	auto it = std::find(_trading_days.begin(), _trading_days.end(), time_str);
	if (it != _trading_days.end()) {
		_day_id = std::distance(_trading_days.begin(), it);
	}
	// need to fix: what it eps release date not in trading day vector?
	else { throw new std::invalid_argument("time_str not in range.");}
}

const TradeDay& TradeDay::move_forward(size_t N) {
	_day_id -= N;
	return *this;
}

const TradeDay& TradeDay::move_backward(size_t N) {
	_day_id += N;
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
