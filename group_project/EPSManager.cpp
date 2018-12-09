#include "pch.h"
#include "EPSManager.h"
#include "utils.h"
#include <vector>
#include <fstream>

EPSManager* EPSManager::_instance = nullptr;

EPSManager* EPSManager::get_instance(const std::string& file_path)
{
	if (!_instance)
	{
		_instance = new EPSManager(file_path);
	}
	return _instance;
}

EPSManager::EPSManager(const std::string& file_path)
{
	std::ifstream file;

	file.open(file_path);

	if (!file.is_open()) throw new std::runtime_error("Cannot open file.");

	auto&& index = read_col_from_csv<std::vector<Ticker>, Ticker>(file, EPS_START_ROW, EPS_INDEX_COL);
	auto&& eps_real = read_col_from_csv<Vector, double>(file, EPS_START_ROW, EPS_EPS_COL);
	auto&& eps_estimate = read_col_from_csv<Vector, double>(file, EPS_START_ROW, EPS_EST_EPS_COL);
	auto&& release_date  = read_col_from_csv<std::vector<std::string>, std::string>(file, EPS_START_ROW, EPS_RE_DATE_COL);
	
	file.close();

	auto&& eps_diff = eps_real / eps_estimate - 1.0;

	const size_t len(eps_diff.size());
	std::vector<TickerInfo> _tmp(len);
	FOR_LOOP(0, i, len)
	{
		_tmp[i] = (std::make_pair(index[i], TradeDay(std::move(release_date[i]))));
	}

	_eps_diff_se = std::move(Series<TickerInfo, false>(_tmp, eps_diff));
}

GroupResult EPSManager::get_group_result() const
{
	GroupResult result(3);

	const size_t len(_eps_diff_se.size());
	auto&& idx = _eps_diff_se.get_index();
	FOR_LOOP(0, i, len)
	{
		if (_eps_diff_se[i] > BAND2 && _eps_diff_se[i] < BAND1)
		{
			result[0].push_back(std::move(idx[i]));
		}
		else if (_eps_diff_se[i] > BAND3 && _eps_diff_se[i] < BAND2)
		{
			result[1].push_back(std::move(idx[i]));
		}
		else if (_eps_diff_se[i] > BAND4 && _eps_diff_se[i] < BAND3)
		{
			result[2].push_back(std::move(idx[i]));
		}
	}

	return result;
}

EPSManager::~EPSManager()
{
	delete _instance;
	_instance = nullptr;
}