/**
 ** \file escapes/escapes-visitor.cc
 ** \brief Implementation for escapes/escapes-visitor.hh.
 */

#include <ast/all.hh>
#include <escapes/escapes-visitor.hh>
#include <misc/contract.hh>

namespace escapes
{
  // FIXED: Some code was deleted here.

  void EscapesVisitor::operator()(ast::FunctionDec& e)
  {
    current_scope++;
    super_type::operator()(e);
    current_scope--;
  }

  void EscapesVisitor::operator()(ast::ForExp& e)
  {
    current_scope++;
    super_type::operator()(e);
    current_scope--;
  }

  void EscapesVisitor::operator()(ast::LetExp& e)
  {
    current_scope++;
    for (auto& it : e.chunks_get())
      {
        (*this)(it);
      }
    // visit the body
    (*this)(e.body_get());
    current_scope--;
  }

  void EscapesVisitor::operator()(ast::VarDec& e)
  {
    scope_var.insert({&e, current_scope});
    super_type::operator()(e);
  }

  void EscapesVisitor::operator()(ast::SimpleVar& e)
  {
    ast::VarDec* var = e.def_get();
    int var_scope = scope_var.find(var)->second;
    /* to ensure the case that one variable is used in the same scope
     * as his declaration scope and in a different scope
     */
    if (var_scope == current_scope && !var->is_locked())
      {
        var->set_unescaped();
      }
    else if (var_scope != current_scope)
      {
        var->set_escaped();
      }
  }
} // namespace escapes
