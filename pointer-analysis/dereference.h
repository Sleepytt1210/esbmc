/*******************************************************************\

Module: Pointer Dereferencing

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#ifndef CPROVER_POINTER_ANALYSIS_DEREFERENCE_H
#define CPROVER_POINTER_ANALYSIS_DEREFERENCE_H

#include <set>

#include <expr.h>
#include <hash_cont.h>
#include <guard.h>
#include <namespace.h>
#include <options.h>

#include "value_sets.h"

class dereference_callbackt
{
public:
  virtual ~dereference_callbackt()
  {
  }

  virtual bool is_valid_object(const irep_idt &identifier)=0;

  virtual void dereference_failure(
    const std::string &property,
    const std::string &msg,
    const guardt &guard)=0;

  typedef hash_set_cont<exprt, irep_hash> expr_sett;

  virtual void get_value_set(
    const exprt &expr,
    value_setst::valuest &value_set)=0;
  
  virtual bool has_failed_symbol(
    const exprt &expr,
    const symbolt *&symbol)=0;
};

class dereferencet
{
public:
  dereferencet(
    const namespacet &_ns,
    contextt &_new_context,
    const optionst &_options,
    dereference_callbackt &_dereference_callback):
    ns(_ns),
    new_context(_new_context),
    options(_options),
    dereference_callback(_dereference_callback)
  { }

  virtual ~dereferencet() { }
  
  typedef enum { READ, WRITE, FREE } modet;

  virtual void dereference(
    exprt &dest,
    const guardt &guard,
    const modet mode);
    
  virtual void add_checks(
    const exprt &dest,
    const guardt &guard,
    const modet mode);

  bool has_dereference(const exprt &expr) const;

  typedef hash_set_cont<exprt, irep_hash> expr_sett;

private:
  const namespacet &ns;
  contextt &new_context;
  const optionst &options;
  dereference_callbackt &dereference_callback;
  static unsigned invalid_counter;

  bool dereference_type_compare(
    exprt &object,
    const typet &dereference_type) const;

  void offset_sum(
    exprt &dest,
    const exprt &offset) const;
  
  void build_reference_to(
    const expr2tc &what,
    const modet mode,
    const expr2tc &deref_expr,
    const type2tc &type,
    expr2tc &value,
    expr2tc &pointer_guard,
    const guardt &guard);

  bool get_value_guard(
    const exprt &symbol,
    const exprt &premise,
    exprt &value);
             
  static const exprt &get_symbol(const exprt &object);
  
  void bounds_check(const class index_exprt &expr, const guardt &guard);
  void valid_check(const exprt &expr, const guardt &guard, const modet mode);

  bool memory_model(
    exprt &value,
    const typet &type,
    const guardt &guard,
    exprt &new_offset);

  bool memory_model_conversion(
    exprt &value,
    const typet &type,
    const guardt &guard,
    exprt &new_offset);
    
  bool memory_model_bytes(
    exprt &value,
    const typet &type,
    const guardt &guard,
    exprt &new_offset);
};

#endif
