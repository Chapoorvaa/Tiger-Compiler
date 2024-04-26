/**
 ** \file llvmtranslate/llvm-type-visitor.cc
 ** \brief Implementation of llvmtranslator::LLVMTypeVisitor.
 */

#include <llvm/IR/DerivedTypes.h>

#include <llvmtranslate/llvm-type-visitor.hh>
#include <type/types.hh>

namespace llvmtranslate
{
  LLVMTypeVisitor::LLVMTypeVisitor(llvm::LLVMContext& ctx)
    : ctx_{ctx}
  {}

  llvm::Type* LLVMTypeVisitor::llvm_type_get() { return type_; }

  llvm::Type* LLVMTypeVisitor::get_record_ltype(const type::Record* e)
  {
    return structs_[e];
  }

  llvm::Type* LLVMTypeVisitor::llvm_type(const type::Type& type)
  {
    operator()(type);
    return type_;
  }

  void LLVMTypeVisitor::operator()(const type::Nil& e)
  {
    if (auto record_type = e.record_type_get())
      type_ = llvm_type(*record_type);
    else
      unreachable();
  }

  void LLVMTypeVisitor::operator()(const type::Void&)
  {
    // FIXED: Some code was deleted here (Void types can be interpreted as int or void type).
    type_ = llvm::Type::getInt32Ty(ctx_);
  }

  void LLVMTypeVisitor::operator()(const type::Int&)
  {
    type_ = llvm::Type::getInt32Ty(ctx_);
  }

  void LLVMTypeVisitor::operator()(const type::String&)
  {
    // Strings are pointers to characters in LLVM.
    // FIXED: Some code was deleted here.
    type_ = llvm::Type::getInt8PtrTy(ctx_);
  }

  void LLVMTypeVisitor::operator()(const type::Named& e)
  {
    // FIXED: Some code was deleted here.
    type_ = llvm_type(e.actual());
  }

  void LLVMTypeVisitor::operator()(const type::Record& e)
  {
    // If the record was never translated, translate it
    if (!structs_[&e])
      {
        // We need to create the struct in two passes to support recursive
        // types, like 'type a = { next : a }
        // So, first we create an empty struct
        structs_[&e] = llvm::StructType::create(ctx_);
        // Then set the body of the structure
        std::vector<llvm::Type*> field_types;
        field_types.reserve(e.fields_get().size());
        // FIXED: Some code was deleted here.
        for (type::Field field : e.fields_get())
        {
            field_types.push_back(llvm_type(field.type_get()));
        }
        structs_[&e]->setBody(std::move(field_types), false);
      }

    type_ = llvm::PointerType::getUnqual(structs_[&e]);
  }

  void LLVMTypeVisitor::operator()(const type::Array& e)
  {
    // Arrays are pointers to the array elements, like in C.
    // FIXED: Some code was deleted here.
    type_ = llvm::PointerType::getUnqual(llvm_type(e.type_get().actual()));
  }

} // namespace llvmtranslate
