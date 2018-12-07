#ifndef DataStructs_h
#define DataStructs_h

#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include "TradeDay.h"
#include "utils.h"


//-----------------------------declairation-start-----------------------------

struct ParseResult {
	int price;
	time_t timestamp;
};

typedef std::string Ticker;

class Vector : public std::vector<double>
{
	friend std::ostream& operator <<(std::ostream& ost, const Vector& v);

public:
	Vector() = default;
	Vector(size_t size);
	Vector(std::vector<double>::iterator begin, std::vector<double>::iterator end);


	Vector operator *(double x);
	Vector operator *(const Vector& r);
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

template <typename T, bool ComparableIndex = true>
class  Series
{
protected:
	size_t _size;

	Vector _values;
	std::vector<T> _index;

	void sort_by_value(size_t start, size_t end);

public:
	friend std::ostream& operator <<(std::ostream& ost, const Series<T>& se)
	{
		FOR_LOOP(0, i, se._size)
		{
			ost << se._index[i] << " " << se._values[i] << std::endl;
		}
		ost << std::endl;

		return ost;
	}
	Series() = default;
	Series(const std::vector<T>& index, const Vector& data); //yes we do want to copy
	Series(const std::string& file_path, unsigned int index_col, unsigned int data_col, unsigned int start_rol);
	
	Series(const Vector& data, int start = 0);
	Series(const Vector&& data, int start = 0);
	Series(const Series&& rhs) noexcept;
	Series(const Series& rhs) = default;
	Series<T, ComparableIndex>& operator =(const Series& rhs);
	Series<T, ComparableIndex>& operator =(const Series&& rhs);

	Vector& get_values();
	std::vector<T>& get_index();

	const Vector& get_values() const;
	const std::vector<T>& get_index() const;

	void set_values(const Vector&& rhs);
	void set_index(const std::vector<T>&& rhs);

	double& operator [](size_t n);
	double operator [](size_t n) const;
	size_t find(const T& key);
	
	Series<T, ComparableIndex> pct_change() const;
	size_t size() const;

	void sort_by_value();
	Series<T, ComparableIndex> right_join(const std::vector<T>& keys);
	Series<T, ComparableIndex> cumsum() const;

	Series<T, ComparableIndex> operator *(double x) const;
	Series<T, ComparableIndex> operator *(const Series& r) const;
	Series<T, ComparableIndex> operator +(double x) const;
	Series<T, ComparableIndex> operator +(const Series& r) const;
	Series<T, ComparableIndex> operator -(double x) const;
	Series<T, ComparableIndex> operator -(const Series& r) const;
	Series<T, ComparableIndex> operator /(double x) const;
	Series<T, ComparableIndex> operator /(const Series& r) const;

	const Series<T, ComparableIndex>& operator +=(double x);
	const Series<T, ComparableIndex>& operator -=(double x);
	const Series<T, ComparableIndex>& operator *=(double x);
	const Series<T, ComparableIndex>& operator /=(double x);
	const Series<T, ComparableIndex>& operator +=(const Series<T, ComparableIndex>& r);
	const Series<T, ComparableIndex>& operator -=(const Series<T, ComparableIndex>& r);
	const Series<T, ComparableIndex>& operator *=(const Series<T, ComparableIndex>& r);
	const Series<T, ComparableIndex>& operator /=(const Series<T, ComparableIndex>& r);
};

typedef std::pair<Ticker, TradeDay> TickerInfo;

typedef std::vector < std::vector<TickerInfo> > GroupResult;

typedef std::vector < std::pair<Vector, Vector> > SummaryMatrix;

class PriceBuff
{
public:
	PriceBuff(const Ticker&& tkr, const Series<TradeDay, false>&& p);
	
	Ticker name;
	Series<TradeDay, false> price;
};

//-----------------------------definition-start-----------------------------
inline Vector::Vector(size_t size) : std::vector<double>(size) { }
inline Vector::Vector(std::vector<double>::iterator begin, std::vector<double>::iterator end) : std::vector<double>(begin, end) { }

inline void set(double& left, double right)
{
	left = right;
}

inline void set(size_t& left, size_t right)
{
	left = right;
}

inline void set(int& left, int right)
{
	left = right;
}

inline void set(TickerInfo& left, int right)
{
	;
}

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex>::Series(const std::vector<T>& index, const Vector& values): _size(index.size()) // possibly problems here
{
	if (index.size() != values.size()) throw new std::invalid_argument("Size of index and value mismatch."); //is that correct?

	_index = index;
	_values = values;
}

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex>::Series(const Series<T, ComparableIndex>&& rhs) noexcept : _index(std::move(rhs._index)), _values(std::move(rhs._values)), _size(rhs._size) { }

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex>::Series(const Vector&& data, int start) : _size(data.size()), _index(_size), _values(std::move(data))
{
	if (ComparableIndex)
	{
		FOR_LOOP(0, i, _size)
		{
			set(_index[i], i + start);
		}
	}
}



template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex>::Series(const Vector& data, int start) : _size(data.size()), _index(_size), _values(data)
{
	if (ComparableIndex)
	{
		FOR_LOOP(0, i, _size)
		{
			set(_index[i], i + start);
		}
	}
}

template <typename T, bool ComparableIndex>
Series<T, ComparableIndex>& Series<T, ComparableIndex>::operator =(const Series&& rhs)
{
	_index = std::move(rhs._index);
	_values = std::move(rhs._values);
	_size = rhs._size;

	return *this;
}

template <typename T, bool ComparableIndex>
Series<T, ComparableIndex>& Series<T, ComparableIndex>::operator =(const Series& rhs)
{
	_index = rhs._index;
	_values = rhs._values;
	_size = rhs._size;

	return *this;
}

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex>::Series(const std::string& file_path, unsigned int index_col, unsigned int data_col, unsigned int start_row)
{
	std::ifstream file;

	file.open(file_path);

	if (!file.is_open()) throw new std::runtime_error("Cannot open file.");

	_index = std::move(read_col_from_csv<std::vector<T>, T>(file, start_row, index_col));
	_values = std::move(read_col_from_csv<Vector, double>(file, start_row, data_col));
	_size = _index.size();

	file.close();
}

template <typename T, bool ComparableIndex>
inline void Series<T, ComparableIndex>::sort_by_value()
{
	if (_size == 0) return;
	
	sort_by_value(0, _size - 1);
}

template <typename T>
size_t _partition(std::vector<T>& index_v, Vector& value_v, size_t start, size_t end)
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
		while (value_v[start] <= value_v[end] && start <= back)
		{
			++start;
		}

		while (value_v[back] >= value_v[end] && start <= back)
		{
			--back;
		}

		if (start >= back)
		{
			break;
		}

		std::swap(value_v[start], value_v[back]);
		std::swap(index_v[start], index_v[back]);
	}

	std::swap(value_v[start], value_v[end]);
	std::swap(index_v[start], index_v[end]);

	return start;
}

template <typename T, bool ComparableIndex>
void Series<T, ComparableIndex>::sort_by_value(size_t start, size_t end)
{
	if (start >= end)
	{
		return;
	}

	size_t pivot = _partition<T>(_index, _values, start, end);
	if (pivot > start + 1)
	{
		sort_by_value(start, pivot - 1);
	}
	if (pivot < end - 1)
	{
		sort_by_value(pivot + 1, end);
	}
}

template <typename T, bool ComparableIndex>
inline Vector& Series<T, ComparableIndex>::get_values()
{
	return _values;
}

template <typename T, bool ComparableIndex>
inline std::vector<T>& Series<T, ComparableIndex>::get_index()
{
	return _index;
}

template <typename T, bool ComparableIndex>
inline const Vector& Series<T, ComparableIndex>::get_values() const
{
	return _values;
}

template <typename T, bool ComparableIndex>
inline const std::vector<T>& Series<T, ComparableIndex>::get_index() const
{
	return _index;
}

template <typename T, bool ComparableIndex>
inline void Series<T, ComparableIndex>::set_values(const Vector&& rhs)
{
	if (rhs.size() != _size) throw new std::invalid_argument("New value mismatch.");

	_values = std::move(rhs);
}

template <typename T, bool ComparableIndex>
inline void Series<T, ComparableIndex>::set_index(const std::vector<T>&& rhs)
{
	if (rhs.size() != _size) throw new std::invalid_argument("New index mismatch.");

	_index = std::move(rhs);
}

template <typename T, bool ComparableIndex>
inline double& Series<T, ComparableIndex>::operator [](size_t n)
{
	return _values[n];
}

template <typename T, bool ComparableIndex>
double Series<T, ComparableIndex>::operator [](size_t n) const
{
	return _values[n];
}

template <typename T, bool ComparableIndex>
inline size_t Series<T, ComparableIndex>::find(const T& key)
{
	size_t idx(0);
	while (idx < _size)
	{
		if (_index[idx] == key)
		{
			break;
		}

		++idx;
	}
	return idx;
}

template <typename T, bool ComparableIndex>
Series<T, ComparableIndex> Series<T, ComparableIndex>::pct_change() const
{
	if (_size == 0)
	{
		throw new std::invalid_argument("Series too short for percent change.");
	}
	
	Series<T, ComparableIndex> _tmp(_size - 1);
	
	FOR_LOOP(0, i, _size - 1)
	{
		_tmp[i] = _values[i + 1] / _values[i] - 1.0; // we are certain that values are double
	}

	_tmp.set_index(std::move(std::vector<T>(++(_index.begin()), _index.end())));
	return _tmp;
}

template <typename T, bool ComparableIndex>
inline size_t Series<T, ComparableIndex>::size() const
{
	return _size;
}

template <typename T, bool ComparableIndex>
Series<T, ComparableIndex> Series<T, ComparableIndex>::right_join(const std::vector<T>& keys)
{
	const size_t k_len(keys.size());
	size_t right(0), pos;
	
	Series<T> tmp(0);
	while (right < k_len)
	{
		pos = find(keys[right]);

		if (pos < _size)
		{
			tmp._index.push_back(keys[right]);
			tmp._values.push_back(_values[pos]);
		}

		++right;
	}

	return tmp;
}

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex> Series<T, ComparableIndex>::operator *(double x) const
{
	Series<T> _tmp(*this);
	_tmp._values *= x;
	return _tmp;
}

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex> Series<T, ComparableIndex>::operator *(const Series<T, ComparableIndex>& r) const
{
	Series<T> _tmp(*this);
	_tmp._values *= r._values;
	return _tmp;
}

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex> Series<T, ComparableIndex>::operator +(double x) const
{
	Series<T> _tmp(*this);
	_tmp._values += x;
	return _tmp;
}

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex> Series<T, ComparableIndex>::operator +(const Series<T, ComparableIndex>& r) const
{
	Series<T> _tmp(*this);
	_tmp._values += r._values;
	return _tmp;
}

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex> Series<T, ComparableIndex>::operator -(double x) const
{
	Series<T> _tmp(*this);
	_tmp._values -= x;
	return _tmp;
}

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex> Series<T, ComparableIndex>::operator -(const Series<T, ComparableIndex>& r) const
{
	Series<T> _tmp(*this);
	_tmp._values -= r._values;
	return _tmp;
}

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex> Series<T, ComparableIndex>::operator /(double x) const
{
	Series<T> _tmp(*this);
	_tmp._values /= x;
	return _tmp;
}

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex> Series<T, ComparableIndex>::operator /(const Series<T, ComparableIndex>& r) const
{
	Series<T> _tmp(*this);
	_tmp._values /= r._values;
	return _tmp;
}

template <typename T, bool ComparableIndex>
inline const Series<T, ComparableIndex>& Series<T, ComparableIndex>::operator +=(double x)
{
	_values += x;
	return *this;
}

template <typename T, bool ComparableIndex>
inline const Series<T, ComparableIndex>& Series<T, ComparableIndex>::operator -=(double x)
{
	_values -= x;
	return *this;
}

template <typename T, bool ComparableIndex>
inline const Series<T, ComparableIndex>& Series<T, ComparableIndex>::operator *=(double x)
{
	_values *= x;
	return *this;
}

template <typename T, bool ComparableIndex>
inline const Series<T, ComparableIndex>& Series<T, ComparableIndex>::operator /=(double x)
{
	_values /= x;
	return *this;
}

template <typename T, bool ComparableIndex>
inline const Series<T, ComparableIndex>& Series<T, ComparableIndex>::operator +=(const Series<T, ComparableIndex>& r)
{
	_values += r._values;
	return *this;
}

template <typename T, bool ComparableIndex>
inline const Series<T, ComparableIndex>& Series<T, ComparableIndex>::operator -=(const Series<T, ComparableIndex>& r)
{
	_values -= r._values;
	return *this;
}

template <typename T, bool ComparableIndex>
inline const Series<T, ComparableIndex>& Series<T, ComparableIndex>::operator *=(const Series<T, ComparableIndex>& r)
{
	_values *= r._values;
	return *this;
}

template <typename T, bool ComparableIndex>
inline const Series<T, ComparableIndex>& Series<T, ComparableIndex>::operator /=(const Series<T, ComparableIndex>& r)
{
	_values /= r._values;
	return *this;
}

template <typename T, bool ComparableIndex>
inline Series<T, ComparableIndex> Series<T, ComparableIndex>::cumsum() const
{
	Series<T> _tmp(_size);
	_tmp.set_values(_values.cumsum());
	return _tmp;
}

std::ostream& operator <<(std::ostream& ost, const TickerInfo& tkr);

inline PriceBuff::PriceBuff(const Ticker&& tkr, const Series<TradeDay, false>&& p) : name(std::move(tkr)), price(std::move(p)) { }
#endif