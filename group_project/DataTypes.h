#ifndef DataStructs_h
#define DataStructs_h

#include <time.h>
#include <string>
#include <vector>
#include "TradeDay.h"

//-----------------------------declairation-start-----------------------------

struct ParseResult {
	int price;
	time_t timestamp;
};

typedef const std::string Ticker;

class Vector : public std::vector<double>
{
public:
	Vector(size_t size); 
	//确定会调用移动构造吗？

	Vector operator *(double x);
	Vector operator *(const Vector& r);
	double operator ^(const Vector& r);

	Vector operator +(double x);
	Vector operator +(const Vector& r);


	Vector operator -(double x);
	Vector operator -(const Vector& r);

	Vector operator /(double x);
	Vector operator /(const Vector& r);

	const Vector& operator +=(double x);
	const Vector& operator -=(double x);
	const Vector& operator *=(double x);
	const Vector& operator /=(double x);

	const Vector& operator +=(const Vector& r);
	const Vector& operator -=(const Vector& r);
	const Vector& operator *=(const Vector& r);
	const Vector& operator /=(const Vector& r);

	Vector cumsum() const;
};

template <typename T>
class Series
{
protected:
	Vector values;
	std::vector<T> index;

	void sort_by_value(size_t start, size_t end); // helper function

public:
	Series(const Vector& data);
	Series(const std::vector<T>&& index, const Vector&& data);
	Series(const Vector& data, int start);

	Vector get_values() const;
	Vector get_index() const;

	void set_values();
	void set_index();

	double& operator [](size_t n);
	Series pct_change() const;
	int size() const;
	void reindex(size_t start, size_t end);
	void read_excel(const std::string& file);

	void sort_by_value(); //a little tricky
	Series common(const Series<T>& rhs);

	Series operator *(double x);
	Series operator *(const Series& r);
	double operator ^(const Series& r);

	Series operator +(double x);
	Series operator +(const Series& r);


	Series operator -(double x);
	Series operator -(const Series& r);

	Series operator /(double x);
	Series operator /(const Series& r);

	const Series& operator +=(double x);
	const Series& operator -=(double x);
	const Series& operator *=(double x);
	const Series& operator /=(double x);

	const Series& operator +=(const Series& r);
	const Series& operator -=(const Series& r);
	const Series& operator *=(const Series& r);
	const Series& operator /=(const Series& r);

	Series cumsum() const;

	virtual ~Series(); //inherented by _PriceBuff
};

typedef std::pair<Ticker, TradeDay> TickerInfo;

typedef std::vector < std::vector<TickerInfo> > GroupResult;

typedef std::vector < std::pair<Vector, Vector> > SummaryMatrix;

//-----------------------------definition-start-----------------------------

inline Vector::Vector(size_t size) : std::vector<double>(size) { }

template <typename T>
inline void Series<T>::sort_by_value()
{
	return sort_by_value(0, size() - 1);
}

template <typename T>
void Series<T>::sort_by_value(size_t start, size_t end)
{
	if (end == 0 || start >= end)
	{
		return;
	}

	size_t pivot = _partition<T>(index, value, start, end);
	sort_by_value(start, pivot - 1);
	sort_by_value(pivot + 1, end);
}

template <typename IndexType>
size_t _partition(std::vector<IndexType> index_v, Vector value_v, size_t start, size_t end)
{
	size_t mid((start + end) / 2), pivot;

	//using median of start, end, mid as pivot
	if (value_v[start] > value_v[end])
	{
		if (value_v[mid] > value_v[start])
		{
			pivot = start;
		}
		else if (value_v[mid] < value_v[end])
		{
			pivot = end;
		}
		else
		{
			pivot = mid;
		}
	}
	else
	{
		if (value_v[mid] > value_v[end])
		{
			pivot = end;
		}
		else if (value_v[mid] < value_v[start])
		{
			pivot = start;
		}
		else
		{
			pivot = mid;
		}
	}

	std::swap(value_v[pivot], value_v[end]);
	std::swap(index_v[pivot], index_v[end]);
	
	size_t back(end - 1);
	while (true)
	{
		while (value_v[start] <= value_v[end])
		{
			++start;
		}

		while (value_v[back]) >= value_v[end])
		{
			--back；
		}

		if (start >= back)
		{
			break;
		}

		std::swap(value_v[start], value_v[back]);
		std::swap(index_v[start], index_v[back]);
	}

	std::swap(value_v[start], value_v[end]);
	std::swap(index_[start], value_v[end]);
}

template <typename T>
std::ostream& operator <<(std::ostream& ost, const Series<T>& se)
{
	const size_t _sz(se.size());

	for (int i(0); i < _sz, ++i)
	{
		ost << se.index[i] << " " << se.data[i] << std::endl;
	}
	ost << std::endl;

	return ost;
}
#endif