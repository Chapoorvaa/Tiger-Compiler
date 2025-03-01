/**
 ** \file overload/type-checker.cc
 ** \brief Implementation for overload/type-checker.hh.
 */

#include <algorithm>
#include <sstream>

#include <misc/indent.hh>
#include <overload/type-checker.hh>
#include <type/types.hh>

namespace overload
{
  TypeChecker::TypeChecker(const overfun_bindings_type& overfun_bindings)
    : overfun_bindings_{overfun_bindings}
  {}

  // FIXME: Some code was deleted here.

} // namespace overload
