#include "pch.h"
#include "DataTypes.h"

Vector Vector::operator *(double x)
{
	const size_t _sz(size());

	Vector _tv(_sz);

	for (size_t i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] * x;
	}

	return _tv;
}

Vector operator *(double x, const Vector& v)
{
	const size_t _sz(v.size());

	Vector _tv(_sz);

	for (size_t i(0); i < _sz; ++i)
	{
		_tv[i] = v[i] * x;
	}

	return _tv;
}

Vector Vector::operator *(const Vector& r)
{
	const size_t _sz(size());

	Vector _tv(_sz);

	for (size_t i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] * r[i];
	}

	return _tv;
}

Vector Vector::operator +(double x)
{
	const size_t _sz(size());

	Vector _tv(_sz);

	for (size_t i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] + x;
	}

	return _tv;
}

Vector operator +(double x, const Vector& v)
{
	const size_t _sz(v.size());

	Vector _tv(_sz);

	for (size_t i(0); i < _sz; ++i)
	{
		_tv[i] = v[i] + x;
	}

	return _tv;
}

Vector Vector::operator +(const Vector& r)
{
	const size_t _sz(size());

	Vector _tv(_sz);

	for (size_t i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] + r[i];
	}

	return _tv;
}

Vector Vector::operator -(double x)
{
	const size_t _sz(size());

	Vector _tv(_sz);

	for (size_t i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] - x;
	}

	return _tv;
}

Vector operator -(double x, const Vector& v)
{
	const size_t _sz(v.size());

	Vector _tv(_sz);

	for (size_t i(0); i < _sz; ++i)
	{
		_tv[i] = x - v[i];
	}

	return _tv;
}

Vector Vector::operator -(const Vector& r)
{
	const size_t _sz(size());

	Vector _tv(_sz);

	for (size_t i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] - r[i];
	}

	return _tv;
}

Vector Vector::operator /(double x)
{
	const size_t _sz(size());

	Vector _tv(_sz);

	for (size_t i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] / x;
	}

	return _tv;
}

Vector Vector::operator /(const Vector& r)
{
	const size_t _sz(size());

	Vector _tv(_sz);

	for (size_t i(0); i < _sz; ++i)
	{
		_tv[i] = (*this)[i] / r[i];
	}

	return _tv;
}

const Vector& Vector::operator +=(double x)
{
	const size_t _sz(size());

	for (size_t i(0); i < _sz; ++i)
	{
		(*this)[i] += x;
	}

	return *this;
}

const Vector& Vector::operator -=(double x)
{
	const size_t _sz(size());

	for (size_t i(0); i < _sz; ++i)
	{
		(*this)[i] -= x;
	}

	return *this;
}

const Vector& Vector::operator *=(double x)
{
	const size_t _sz(size());

	for (size_t i(0); i < _sz; ++i)
	{
		(*this)[i] *= x;
	}

	return *this;
}

const Vector& Vector::operator /=(double x)
{
	const size_t _sz(size());

	for (size_t i(0); i < _sz; ++i)
	{
		(*this)[i] /= x;
	}

	return *this;
}

const Vector& Vector::operator +=(const Vector& r)
{
	const size_t _sz(size());

	for (size_t i(0); i < _sz; ++i)
	{
		(*this)[i] += r[i];
	}

	return *this;
}

const Vector& Vector::operator -=(const Vector& r)
{
	const size_t _sz(size());

	for (size_t i(0); i < _sz; ++i)
	{
		(*this)[i] -= r[i];
	}

	return *this;
}

const Vector& Vector::operator *=(const Vector& r)
{
	const size_t _sz(size());

	for (size_t i(0); i < _sz; ++i)
	{
		(*this)[i] *= r[i];
	}

	return *this;
}

const Vector& Vector::operator /=(const Vector& r)
{
	const size_t _sz(size());

	for (size_t i(0); i < _sz; ++i)
	{
		(*this)[i] /= r[i];
	}

	return *this;
}

Vector Vector::cumsum() const
{
	const size_t _sz(size());

	if (_sz == 0)
	{
		return Vector(0);
	}

	Vector _tmp(_sz);
	double _t_sum(0.0);

	for (size_t i(0); i < _sz; ++i)
	{
		_t_sum = _tmp[i] = (*this)[i] + _t_sum; //is this correct?
	}

	return _tmp;
}

std::ostream& operator <<(std::ostream& ost, const Vector& v)
{
	for (const auto& it : v)
	{
		ost << it << std::endl;
	}
	ost << std::endl;

	return ost;
}

std::ostream& operator <<(std::ostream& ost, const TickerInfo& tkr)
{
	ost << tkr.first << std::endl;
	return ost;
}