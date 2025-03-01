/**
 ** \file inlining/pruner.hh
 ** \brief Declaration of inlining::Pruner.
 */

#pragma once

#include <map>

#include <astclone/cloner.hh>
#include <misc/set.hh>

namespace inlining
{
  /// Prune useless function declarations within an AST.
  class Pruner : public astclone::Cloner
  {
  public:
    using super_type = astclone::Cloner;

    // Import overloaded virtual functions.
    using super_type::operator();

    using func_vect = std::vector<ast::FunctionDec*>;
    using func_count = std::map<misc::symbol, int>;

    /// \name Visit methods.
    /// \{
    // FIXME: Some code was deleted here.
    /// \}

    ast::FunctionChunk* prune(ast::FunctionChunk& e);

  private:
    // Keep track of current nested functions
    std::vector<const ast::FunctionDec*> current_functions_;

    // Associate function dec with the number of CallExp calling it
    func_count called_functions_;
  };

} // namespace inlining
