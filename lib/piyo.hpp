#pragma once
#include <array>
#include <iomanip>
#include <limits>

namespace Shell {
struct Piyoyo {
  int value;
  int getValue() { return value; }
  void setValue(int val) { value = val; }
  static Piyoyo StaticFunc() { return Piyoyo(); }
};

using Vec2 = std::array<float, 2>;
using Vec3 = std::array<float, 3>;

template <typename T = float> struct Range {
  T min, max;
  Range() { clear(); }
  Range(T min_, T max_) {
    min = min_;
    max = max_;
  }
  template <typename U> Range(const Range<U>& o) {
    min = o.min;
    max = o.max;
  }
  void clear() {
    min = std::numeric_limits<T>::max();
    max = std::numeric_limits<T>::lowest();
  }
  [[nodiscard]] bool contains(float t) const { return min <= t && t <= max; }
  [[nodiscard]] bool contains(const Range& t) const { return min <= t.min && t.max <= max; }
  [[nodiscard]] std::string str() const { return "Range(" + std::to_string(min) + ", " + std::to_string(max) + ")"; }
};

struct Rect {
  Range<float> x, y;
  Rect() { x.min = y.min = x.max = y.max = 0; }
  template <typename T> Rect(const Range<T>& xr, const Range<T>& yr) {
    x = xr;
    y = yr;
  }
  Rect(float xmin, float xmax, float ymin, float ymax) {
    x.min = xmin;
    x.max = xmax;
    y.min = ymin;
    y.max = ymax;
  }
  [[nodiscard]] float top() const { return y.min; }
  [[nodiscard]] float bottom() const { return y.max; }
  [[nodiscard]] float left() const { return x.min; }
  [[nodiscard]] float right() const { return x.max; }

  // cppygen off
  /* float& top() { return y.min; } */
  /* float& bottom() { return y.max; } */
  /* float& left() { return x.min; } */
  /* float& right() { return x.max; } */
  // cppygen on

  [[nodiscard]] bool contains(const Rect& other) const { return x.contains(other.x) && y.contains(other.y); }

  bool contains(const float x_, const float y_) const { return x.contains(x_) && y.contains(y_); }

  [[nodiscard]] std::string str() const { return "Rect3D( [x,y] = " + x.str() + ", " + y.str() + ", " + ")"; }
};

template <typename T> inline std::ostream& operator<<(std::ostream& os, const Range<T>& r) {
  return os << r.str();
}

template <typename T> inline std::ostream& operator<<(std::ostream& os, const Rect& r) {
  return os << r.str();
}

} // namespace Shell
