#include "piyo.hpp"
#include "hoge.hpp"
#include <vector>

namespace Shell::piyo {
Piyoyo make_piyoyo() {
  Piyoyo tmp;
  tmp.setValue(-5);
  return tmp;
}
std::vector<double> fugafuga() { return {3, 4, 5, 6}; }

// cppygen off
template<typename T>
std::ostream& operator<<(std::ostream& os, const Range<T>& r){
  os << r.str();
  return os;
}
template std::ostream& operator<<(std::ostream& os, const Range<float>& r);
template std::ostream& operator<<(std::ostream& os, const Range<int>& r);
// cppygen on

} // namespace Shell::piyo
