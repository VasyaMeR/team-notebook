/**
 * Author: Vasyl Merenych
 * Date: 2024-01-10
 * License: CC0
 * Source: folklore
 * Description: Geometry formuls
 * Time: 
 * Status: -
 */


#include <complex>
#include <iostream>

class point : public std::complex<long double> {
	using ld = long double;
	static constexpr long double PI = 3.141592653589793;

public:
	point() : std::complex<long double>() {}

	point(ld x, ld y) : std::complex<long double>(x, y) {}

	point(std::complex<long double> obj) : std::complex<long double>(obj) {}

	ld x() {
		return this->real();
	}

	ld y() {
		return this->imag();
	}

	ld x() const {
		return this->real();
	}

	ld y() const {
		return this->imag();
	}

	// a_x * b_x + a_y * b_y
	static ld dot_product(const point& a, const point& b) {
		return (conj(a) * b).real();
	}


	// a_x * b_y - a_y * b_x
	static ld cross_product(const point& a, const point& b) {
		return (conj(a) * b).imag();
	}

	static ld squared_distance(const point& a, const point& b) {
		return norm(a - b);
	}

	static ld distance(const point& a, const point& b) {
		return abs(a - b);
	}

	// angle_of_elevation of line (a, b) to oX
	static ld angle_of_elevation(const point& a, const point& b) {
		return arg(b - a);
	}

	// k from y = k * x + b
	static ld slope_of_line(const point& a, const point& b) {
		return tan(arg(b - a));
	}

	static point from_polar(ld r, ld theta) {
		return std::polar(r, theta);
	}

	static point rotate_above_pivot(const point& a, const ld theta, const point& pivot = point(0, 0)){
		return (a - pivot) * std::polar<ld>(1.0, theta) + pivot;
	}

	point& rotate(const ld theta, const point& pivot = point(0, 0)) {
		*this = point::rotate_above_pivot(*this, theta, pivot);
		return *this;
	}

	// angle of ABC
	static ld angle(const point& a, const point& b, const point& c) {
		return abs(remainder(arg(a-b) - arg(c-b), 2.0 * PI));
	}

	static point project_on_vector(const point& p, const point& v) {
		return v * dot_product(p, v) / norm(v);
	}

	static point project_on_line(const point& p, const point& a, const point& b) {
		return a + (b - a) * dot_product(p - a, b - a) / norm(b - a);
	}

	static point reflect_accros(const point& p, const point& a, const point& b) {
		return a + conj((p - a) / (b - a)) * (b - a);
	}

	// intersection of lines (a, b) and (p, q). if parallel returns {false, ...} else {true, intersection}.
	friend std::pair<bool, point> intersection_of_lines(const point& a, const point& b, const point& p, const point& q) {
		ld c1 = cross_product(p - a, b - a), c2 = cross_product(q - a, b - a);
		if (c1 == c2) {
			return {false, {}};
		}
		return {true, (c1 * q - c2 * p) / (c1 - c2)}; // undefined if parallel
	}

	// returns a, b, c from a * x + b * y + c == 0 by two points
	friend std::tuple<ld, ld, ld> get_line(const point& p, const point& q) {
		ld a = (p.y() - q.y());
		ld b = -(p.x() - q.x());
		ld c = p.y() * (p.x() - q.x()) - p.x() * (p.y() - q.y());
		return {a, b, c};
	}

	friend ld distance_from_point_to_line(const point& p, const point& a, const point& b) {
		point q = project_on_line(p, a, b);

		return point::distance(p, q);
	}

	friend ld distance_from_point_to_segment(const point& p, const point& a, const point& b) {
		point q = project_on_line(p, a, b);
		if (std::min(a.x(), b.x()) <= q.x() && q.x() <= std::max(a.x(), b.x()))
			return point::distance(p, q);
		else
			return std::min(distance(p, a), distance(p, b));
	}

	friend std::istream& operator>> (std::istream& in, point& p) {
		ld x, y;
		in >> x >> y;
		p = point(x, y);
		return in; 
	}
};