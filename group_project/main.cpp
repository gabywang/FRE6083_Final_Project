#include "pch.h"

#if 1
#include "DataTypes.h"
#include "HistDataManager.h"
#include "EPSManager.h"
#include "SampleManager.h"
#include "PlotManager.h"
#include "configure.h"

int main()
{
	HistDataFetcher* hist_data_fetcher(HistDataFetcher::get_instance());
	HistDataManager* hist_data_manager(HashHistDataManager::get_instance(hist_data_fetcher));
	EPSManager* eps_manager(EPSManager::get_instance(EPS_FILE));
	SampleManager* sample_manager(new SampleManager(eps_manager->get_group_result()));
	PlotManager* plot_manager(PlotManager::get_instance());

	SummaryMatrix result;
	Series<TradeDay, false>&& index_se(hist_data_fetcher->get_ticker_price(INDEX_TKR, TradeDay(INDEX_START), TradeDay(INDEX_END)).price);

	FOR_LOOP(0, i, SAMPLE_COUNT)
	{
		Vector aar(PRICE_LENGTH - 1);
		Vector caar(PRICE_LENGTH - 1);
		const GroupResult&& sample = sample_manager->get_sample(SAMPLE_SIZE);

		FOR_LOOP(0, group_id, sample.size())
		{
			aar = 0;
			caar = 0;

			for (auto& info_pair : sample[group_id])
			{
				Series<TradeDay, false>&& tkr_se = hist_data_manager->get_ticker(info_pair.first, info_pair.second, PRICE_LENGTH);
				Series<TradeDay, false>&& index_common = index_se.right_join(tkr_se.get_index());
				aar += (tkr_se.pct_change() - index_common.pct_change()).get_values();
			}

			aar /= TOTAL_STOCK_NUM / GROUP_COUNT;
			caar = aar.cumsum();

			if (i == 0)
			{
				result.push_back(std::move(std::make_pair(aar, caar)));
			}
			else
			{
				result[group_id].first += aar;
				result[group_id].second += caar;
			}
		}
	}
	
	for (auto &it : result)
	{
		it.first /= SAMPLE_COUNT;
		it.second /= SAMPLE_COUNT;

		plot_manager->plot(Series<int>(it.first, -int(PRICE_LENGTH / 2)));
		plot_manager->plot(Series<int>(it.second, -int(PRICE_LENGTH / 2)));
	}
	
	delete sample_manager;
	delete eps_manager;

	return 0;
}
#endif

#if 0
#include "pch.h"
#include "Menu.h"

int main()
{
	Menu* menu = Menu::get_instance();
	return menu->run_forever();
}
#endif