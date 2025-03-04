#ifndef CODE_SPACE_JOT_KNOW_ENUM_HPP
#define CODE_SPACE_JOT_KNOW_ENUM_HPP

#include <sstream>
#include <string>

namespace jot {
// It is used to limit the number of enum values that can be passed to the get_enum_name function.
// If the enum value is greater than know_enum_max_value, the function will throw an exception.
constexpr int know_enum_max_value = 10;
} // namespace jot

namespace jot {
namespace detail {
// get_enum_name_static is a helper function that returns
// the name of the enum value in a static compile time.
template <typename T, T N>
const char *get_enum_name_static() {
#ifdef __clang__
  return __PRETTY_FUNCTION__;
#elif defined(__GNUC__)
  return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
  return __FUNCSIG__;
#endif
}

template <bool Cond>
struct enable_if__ {};

template <>
struct enable_if__<true> {
  using type = void;
};

// static_for is a helper function that calls a function
// for each value in a range in static compile time.
template <int Begin, int End, typename F>
typename jot::detail::enable_if__<Begin == End>::type static_for(F &&func) {}

template <int Begin, int End, typename F>
typename jot::detail::enable_if__<Begin != End>::type static_for(F &&func) {
  func.template call<Begin>();
  static_for<Begin + 1, End>(std::forward<F>(func));
}

template <typename T>
struct get_enum_name_functor {
  int n_;
  std::string &s_;
  get_enum_name_functor(int n, std::string &s) : n_(n), s_(s) {}

  template <int N>
  void call() const {
    if (n_ == N) {
      s_ = jot::detail::get_enum_name_static<T, (T)N>();
    }
  }
};

template <typename T, T Begin, T End>
std::string get_enum_name(T n) {
  std::string s;
  jot::detail::static_for<(int)Begin, (int)End>(jot::detail::get_enum_name_functor<T>((int)n, s));
  if (s.empty()) {
    return "";
  }
#if defined(__clang__) || defined(__GNUC__)
  size_t pos = s.find("N = ");
  pos += 4;
  size_t end = s.find_first_of(";]", pos);
#elif defined(_MSC_VER)
  size_t pos = s.find(",");
  pos += 1;
  size_t end = s.find(">", pos);
#endif
  s = s.substr(pos, end - pos);
  // remove namespace name and enum name prefix
  size_t last_colon = s.rfind("::");
  s = s.substr(last_colon + 2);
  return s;
}

} // namespace detail

/**
 * @brief Get the enum name object
 *
 * @tparam T enum type
 * @param n enum value
 * @return std::string enum name
 * @throws std::invalid_argument when enum value is invalid.
 */
template <typename T>
std::string get_enum_name(T n) {
  std::string s = jot::detail::get_enum_name<T, (T)0, (T)jot::know_enum_max_value>(n);
  if (s.empty()) {
    std::stringstream ss;
    ss << "Invalid enum value: " << (int)n;
    throw std::invalid_argument(ss.str());
  }
  return s;
}

/**
 * @brief determine whether the input enum is valid
 *
 * @tparam T enum type
 * @param name enum name
 * @return true or false
 */
template <typename T>
bool enum_contains(T n) {
  std::string s = jot::detail::get_enum_name<T, (T)0, (T)jot::know_enum_max_value>(n);
  return !s.empty();
}

namespace detail {
template <typename T, T Begin, T End>
T enum_from_name(const std::string &name) {
  for (int i = (int)Begin; i <= (int)End; ++i) {
    if (jot::get_enum_name((T)i) == name) {
      return (T)i;
    }
  }
  std::stringstream ss;
  ss << "Invalid enum name: " << name;
  throw std::invalid_argument(ss.str());
}
} // namespace detail

/**
 * @brief Get the enum value from name object, if the name is invalid, throw an exception
 * @tparam T enum type
 * @param name enum name
 * @return T enum value
 * @throws std::invalid_argument when name is empty or not found in enum range.
 */
template <typename T>
T enum_from_name(const std::string &name) {
  if (name.empty()) {
    std::stringstream ss;
    ss << "Invalid enum name: " << name;
    throw std::invalid_argument(ss.str());
  }
  // Directly call the internal implementation, pass exceptions to the caller
  // ensure exception safety
  return jot::detail::enum_from_name<T, (T)0, (T)jot::know_enum_max_value>(name);
}
} // namespace jot

#endif // CODE_SPACE_JOT_KNOW_ENUM_HPP
