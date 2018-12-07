#ifndef HistDataManager_h
#define HistDataManager_h

#include "HistDataFetcher.h"
#include "TradeDay.h"

#include <unordered_map>

class HistDataManager
{
protected:
	class _PriceBuff : public Series<TradeDay>
	{
	private:
		friend HistDataManager;

	protected:
		time_t arrive_time;
	};

	static HistDataFetcher* _fetcher;

	HistDataManager();
	HistDataManager(const HistDataManager& dm);
	HistDataManager& operator =(const HistDataManager& rhs);

public:
	virtual Series<TradeDay> get_ticker(const Ticker&& tkr, TradeDay mid, int N) = 0;

	virtual void flush() = 0;

	virtual ~HistDataManager();
};

class HashHistDataManager : public HistDataManager
{
protected:
	HashHistDataManager();
	HashHistDataManager(const HashHistDataManager& dm);
	HashHistDataManager& operator =(const HashHistDataManager& rhs);

	//std::unordered_map<Ticker, _PriceBuff*> _hmap;
	
	void _pop_foremost(); //当储存的Price太多，hash_map性能下降，内存占用大，需要删除一个，O(n)

public:
	static HistDataManager* get_instance(HistDataFetcher* hdf)
	{
		_fetcher = hdf;
		static HashHistDataManager _instance; // no worry about destruct?
		return &_instance;
	}

	virtual Series<TradeDay> get_ticker(const Ticker&& tkr, TradeDay mid, int N) override; //little tricky

	virtual void flush() override;

	virtual ~HashHistDataManager();
};

inline HistDataManager::HistDataManager()
{
	;
}

inline HistDataManager::HistDataManager(const HistDataManager& dm)
{
	;
}

inline HistDataManager& HistDataManager::operator =(const HistDataManager& rhs)
{
	;
}

inline HistDataManager::~HistDataManager()
{
	;
}

inline HashHistDataManager::HashHistDataManager()
{
	;
}

inline HashHistDataManager::HashHistDataManager(const HashHistDataManager& dm)
{
	;
}

inline HashHistDataManager& HashHistDataManager::operator =(const HashHistDataManager& rhs)
{
	;
}

inline HashHistDataManager::~HashHistDataManager()
{
	;
}
#endif

