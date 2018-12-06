#ifndef DataStructs_h
#define DataStructs_h

#include <time.h>
#include <string>
#include <vector>

//-----------------------------declairation-start-----------------------------

struct ParseResult {
	int price;
	time_t timestamp;
};

typedef const std::string Ticker;

class Vector : public std::vector<double>
{
public:
	Vector(size_t size); //确定会调用移动构造吗？

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
public:
	Vector values;
	std::vector<T> index;

	Series(const Vector& data);
	Series(const std::vector<T>&& index, const Vector&& data);
	Series(const Vector& data, int start);

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

inline Vector Vector::operator *(double x)
{
	const int _sz(size());

	Vector _tv(_sz);

	for (int i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] * x;
	}

	return _tv;
}

inline Vector operator *(double x, const Vector& v)
{
	const int _sz(v.size());

	Vector _tv(_sz);

	for (int i(0); i < _sz; ++i)
	{
		_tv[i] = v[i] * x;
	}

	return _tv;
}

inline Vector Vector::operator *(const Vector& r)
{
	const int _sz(size());

	Vector _tv(_sz);

	for (int i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] * r[i];
	}

	return _tv;
}


inline double Vector::operator ^(const Vector& r)
{
	double _ans(0.0);

	const int _sz(size());

	for (int i(0); i < _sz; ++i)
	{
		_ans += (*this)[i] * r[i];
	}

	return _ans;
}


inline Vector Vector::operator +(double x)
{
	const int _sz(size());

	Vector _tv(_sz);

	for (int i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] + x;
	}

	return _tv;
}

inline Vector operator +(double x, const Vector& v)
{
	const int _sz(v.size());

	Vector _tv(_sz);

	for (int i(0); i < _sz; ++i)
	{
		_tv[i] = v[i] + x;
	}

	return _tv;
}

inline Vector Vector::operator +(const Vector& r)
{
	const int _sz(size());

	Vector _tv(_sz);

	for (int i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] + r[i];
	}

	return _tv;
}

inline Vector Vector::operator -(double x)
{
	const int _sz(size());

	Vector _tv(_sz);

	for (int i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] - x;
	}

	return _tv;
}

inline Vector operator -(double x, const Vector& v)
{
	const int _sz(v.size());

	Vector _tv(_sz);

	for (int i(0); i < _sz; ++i)
	{
		_tv[i] = x - v[i];
	}

	return _tv;
}

inline Vector Vector::operator -(const Vector& r)
{
	const int _sz(size());

	Vector _tv(_sz);

	for (int i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] - r[i];
	}

	return _tv;
}

inline Vector Vector::operator /(double x)
{
	const int _sz(size());

	Vector _tv(_sz);

	for (int i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] / x;
	}

	return _tv;
}

inline Vector Vector::operator /(const Vector& r)
{
	const int _sz(size());

	Vector _tv(_sz);

	for (int i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] / r[i];
	}

	return _tv;
}

inline const Vector& Vector::operator +=(double x)
{
	const int _sz(size());

	for (int i(0); i < _sz; ++i)
	{
		(*this)[i] += x;
	}

	return *this;
}

inline const Vector& Vector::operator -=(double x)
{
	const int _sz(size());

	for (int i(0); i < _sz; ++i)
	{
		(*this)[i] -= x;
	}

	return *this;
}

inline const Vector& Vector::operator *=(double x)
{
	const int _sz(size());

	for (int i(0); i < _sz; ++i)
	{
		(*this)[i] *= x;
	}

	return *this;
}

inline const Vector& Vector::operator /=(double x)
{
	const int _sz(size());

	for (int i(0); i < _sz; ++i)
	{
		(*this)[i] /= x;
	}

	return *this;
}

inline const Vector& Vector::operator +=(const Vector& r)
{
	const int _sz(size());

	for (int i(0); i < _sz; ++i)
	{
		(*this)[i] += r[i];
	}

	return *this;
}

inline const Vector& Vector::operator -=(const Vector& r)
{
	const int _sz(size());

	for (int i(0); i < _sz; ++i)
	{
		(*this)[i] -= r[i];
	}

	return *this;
}

inline const Vector& Vector::operator *=(const Vector& r)
{
	const int _sz(size());

	for (int i(0); i < _sz; ++i)
	{
		(*this)[i] *= r[i];
	}

	return *this;
}

inline const Vector& Vector::operator /=(const Vector& r)
{
	const size_t _sz(size());

	for (int i(0); i < _sz; ++i)
	{
		(*this)[i] /= r[i];
	}

	return *this;
}

inline Vector Vector::cumsum() const
{
	const size_t _sz(size());
	
	if (_sz == 0)
	{
		return Vector(0);
	}
	
	Vector _tmp(_sz);
	double _t_sum(0.0);

	for (int i(0); i < _sz; ++i)
	{
		_t_sum = _tmp[i] = (*this)[i] + _t_sum; //is this correct?
	}

	return _tmp;
}

inline std::ostream& operator <<(std::ostream& ost, const Vector& v)
{
	for (const auto& it : v)
	{
		ost << it << std::endl;
	}
	ost << std::endl;

	return ost;
}

template <typename T>
inline std::ostream& operator <<(std::ostream& ost, const Series<T>& se)
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