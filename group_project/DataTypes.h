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

typedef const std::string Ticker;

class Vector : public std::vector<double>
{
	friend std::ostream& operator <<(std::ostream& ost, const Vector& v);

public:
	Vector(size_t size);
	Vector();

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

template <typename T>
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

	Series(const std::vector<T> index, const Vector data); //yes we do want to copy
	Series(const Vector&& data, int start = 0);
	Series(const std::string&& file_path, unsigned int index_col, unsigned int data_col, unsigned int start_rol);

	Vector& get_values();
	std::vector<T>& get_index();

	const Vector& get_values() const;
	const std::vector<T>& get_index() const;

	void set_values(const Vector&& rhs);
	void set_index(const std::vector<T>&& rhs);

	double& operator [](size_t n);
	size_t find(const T& key);
	
	Series<T> pct_change() const;
	size_t size() const;

	void sort_by_value();
	Series<T> right_join(const std::vector<T>& keys);
	Series<T> cumsum() const;

	Series<T> operator *(double x) const;
	Series<T> operator *(const Series& r) const;
	Series<T> operator +(double x) const;
	Series<T> operator +(const Series& r) const;
	Series<T> operator -(double x) const;
	Series<T> operator -(const Series& r) const;
	Series<T> operator /(double x) const;
	Series<T> operator /(const Series& r) const;

	const Series<T>& operator +=(double x);
	const Series<T>& operator -=(double x);
	const Series<T>& operator *=(double x);
	const Series<T>& operator /=(double x);
	const Series<T>& operator +=(const Series<T>& r);
	const Series<T>& operator -=(const Series<T>& r);
	const Series<T>& operator *=(const Series<T>& r);
	const Series<T>& operator /=(const Series<T>& r);
};

typedef std::pair<Ticker, TradeDay> TickerInfo;

typedef std::vector < std::vector<TickerInfo> > GroupResult;

typedef std::vector < std::pair<Vector, Vector> > SummaryMatrix;


//-----------------------------definition-start-----------------------------
inline Vector::Vector(size_t size) : std::vector<double>(size) { }
inline Vector::Vector() : std::vector<double>() { }

template <typename T>
inline Series<T>::Series(const std::vector<T> index, const Vector values): _size(index.size()) // possibly problems here
{
	if (index.size() != values.size()) throw new std::invalid_argument("Size of index and value mismatch."); //is that correct?

	_index = std::move(index);
	_values = std::move(values);
}

template <typename T>
inline Series<T>::Series(const Vector&& data, int start): _size(data.size()), _index(_size), _values(std::move(data))
{
	FOR_LOOP(0, i, _size)
	{
		_index[i] = i + start;
	}
}

template <typename T>
inline Series<T>::Series(const std::string&& file_path, unsigned int index_col, unsigned int data_col, unsigned int start_row)
{
	std::ifstream file;

	file.open(file_path);

	if (!file.is_open()) throw new std::runtime_error("Cannot open file.");

	_index = std::move(read_col_from_csv<std::vector<T>, T>(file, start_row, index_col));
	_values = std::move(read_col_from_csv<Vector, double>(file, start_row, data_col));
	_size = _index.size();

	file.close();
}

template <typename T>
inline void Series<T>::sort_by_value()
{
	return sort_by_value(0, _size - 1);
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

template <typename T>
void Series<T>::sort_by_value(size_t start, size_t end)
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

template <typename T>
inline Vector& Series<T>::get_values()
{
	return _values;
}

template <typename T>
inline std::vector<T>& Series<T>::get_index()
{
	return _index;
}

template <typename T>
inline const Vector& Series<T>::get_values() const
{
	return _values;
}

template <typename T>
inline const std::vector<T>& Series<T>::get_index() const
{
	return _index;
}

template <typename T>
inline void Series<T>::set_values(const Vector&& rhs)
{
	if (rhs.size() != _size) throw new std::invalid_argument("New value mismatch.");

	_values = std::move(rhs);
}

template <typename T>
inline void Series<T>::set_index(const std::vector<T>&& rhs)
{
	if (rhs.size() != _size) throw new std::invalid_argument("New index mismatch.");

	_index = std::move(rhs);
}

template <typename T>
inline double& Series<T>::operator [](size_t n)
{
	return _values[n];
}

template <typename T>
inline size_t Series<T>::find(const T& key)
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

template <typename T>
Series<T> Series<T>::pct_change() const
{
	if (_size == 0)
	{
		throw new std::invalid_argument("Series too short for percent change.");
	}
	
	Series<T> _tmp(_size - 1);
	
	FOR_LOOP(0, i, _size - 1)
	{
		_tmp[i] = _values[i + 1] / _values[i] - 1.0; // we are certain that values are double
	}

	return _tmp;
}

template <typename T>
inline size_t Series<T>::size() const
{
	return _size;
}

template <typename T>
Series<T> Series<T>::right_join(const std::vector<T>& keys)
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

template <typename T>
inline Series<T> Series<T>::operator *(double x) const
{
	Series<T> _tmp(*this);
	_tmp._values *= x;
	return _tmp;
}

template <typename T>
inline Series<T> Series<T>::operator *(const Series<T>& r) const
{
	Series<T> _tmp(*this);
	_tmp._values *= r._values;
	return _tmp;
}

template <typename T>
inline Series<T> Series<T>::operator +(double x) const
{
	Series<T> _tmp(*this);
	_tmp._values += x;
	return _tmp;
}

template <typename T>
inline Series<T> Series<T>::operator +(const Series<T>& r) const
{
	Series<T> _tmp(*this);
	_tmp._values += r._values;
	return _tmp;
}

template <typename T>
inline Series<T> Series<T>::operator -(double x) const 
{
	Series<T> _tmp(*this);
	_tmp._values -= x;
	return _tmp;
}

template <typename T>
inline Series<T> Series<T>::operator -(const Series<T>& r) const
{
	Series<T> _tmp(*this);
	_tmp._values -= r._values;
	return _tmp;
}

template <typename T>
inline Series<T> Series<T>::operator /(double x) const
{
	Series<T> _tmp(*this);
	_tmp._values /= x;
	return _tmp;
}

template <typename T>
inline Series<T> Series<T>::operator /(const Series<T>& r) const
{
	Series<T> _tmp(*this);
	_tmp._values /= r._values;
	return _tmp;
}

template <typename T>
inline const Series<T>& Series<T>::operator +=(double x)
{
	_values += x;
	return *this;
}

template <typename T>
inline const Series<T>& Series<T>::operator -=(double x)
{
	_values -= x;
	return *this;
}

template <typename T>
inline const Series<T>& Series<T>::operator *=(double x)
{
	_values *= x;
	return *this;
}

template <typename T>
inline const Series<T>& Series<T>::operator /=(double x)
{
	_values /= x;
	return *this;
}

template <typename T>
inline const Series<T>& Series<T>::operator +=(const Series<T>& r)
{
	_values += r._values;
	return *this;
}

template <typename T>
inline const Series<T>& Series<T>::operator -=(const Series<T>& r)
{
	_values -= r._values;
	return *this;
}

template <typename T>
inline const Series<T>& Series<T>::operator *=(const Series<T>& r)
{
	_values *= r._values;
	return *this;
}

template <typename T>
inline const Series<T>& Series<T>::operator /=(const Series<T>& r)
{
	_values /= r._values;
	return *this;
}

template <typename T>
inline Series<T> Series<T>::cumsum() const
{
	Series<T> _tmp(_size);
	_tmp.set_values(_values.cumsum());
	return _tmp;
}

#endif