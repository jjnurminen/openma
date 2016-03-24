/* 
 * Open Source Movement Analysis Library
 * Copyright (C) 2016, Moveck Solution Inc., all rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

%module base

%{
#include "openma/base.h"
%}

%include "reference_counting.i"

%include <std_string.i>

// ========================================================================= //
//                               UTIL FUNCTIONS
// ========================================================================= //

%define SWIG_TYPEMAP_OUT_CONSTRUCTOR(typename)
// Need to verify if the generated object is not null before being added in the workspace.
%typemap(check, noblock=1) ma:: ## typename* ma:: ## typename:: ## typename
{
  if (!result) {
    SWIG_exception_fail(SWIG_RuntimeError, "Impossible to create or cast an object of type 'ma::typename' with given input(s)");
  }
  _out = SWIG_NewPointerObj(SWIG_as_voidptr(result), $descriptor(ma:: ## typename*), 1 | 0);
};
/*// Same thing for the clone() method
%typemap(out, noblock=1) ma:: ## typename* ma:: ## typename::clone
{
  _out = SWIG_NewPointerObj(SWIG_as_voidptr(result), $descriptor(ma:: ## typename*), 1 | 0);
  if (result->hasParents()) _ma_refcount_incr(result);
};*/
%enddef

%define SWIG_EXTEND_CAST_CONSTRUCTOR(typename, swigtype)
%extend {
typename(swigtype* other)
{
  void* argp1 = nullptr;
  int res1 = SWIG_ConvertPtr(other, &argp1, SWIGTYPE_p_ma__Node, 0 |  0 );
  if (!SWIG_IsOK(res1))
  {
    SWIG_Error(SWIG_ArgError(res1), "in method 'new_" "typename" "', argument 1 of type 'ma::Node *'");
    return nullptr;
  }
  return ma::node_cast<ma::## typename*>(reinterpret_cast<ma::Node*>(argp1));
};
};
%enddef 

%{
void _ma_clear_node(ma::Node* self)
{
  int count = 0;
  // Unref parents
  auto p1 = self->parents();
  for (auto parent : p1)
  {
    count = _ma_refcount_decr(self);
    self->removeParent(parent);
  }
  assert(count >= 0);
  // Unref children
  auto c1 = self->children();
  for (auto child : c1)
    _ma_refcount_decr(child);
  // Detach remaining children (still in the workspace)
  auto c2 = self->children();
  for (auto child : c2)
    child->removeParent(self);
  // Node clear
  self->clear();
  // Reset the reference counter
  _ma_refcount_reset(self, count);
};
%};

%define SWIG_EXTEND_DEEPCOPY(typename)
%extend {
void copy(ma::Node* source)
{
  _ma_clear_node($self);
  int count = _ma_refcount_set(source);
  $self->copy(source);
  _ma_refcount_reset($self, count, false);
  auto& children = $self->children();
  for (auto child : children)
    _ma_refcount_reset(child, 0);
};
%newobject clone;
typename* clone(Node* parent = nullptr) const
{
  ma::typename* ptr = $self->clone(parent);
  _ma_refcount_reset(ptr, -1, false); // -1: because the SWIG generated code will take the ownership
  if (parent != nullptr) _ma_refcount_incr(ptr);
  auto& children = ptr->children();
  for (auto child : children)
    _ma_refcount_reset(child, 0);
  return ptr;
};
};
%enddef 

// ========================================================================= //
//                                INTERFACE
// ========================================================================= //

// Use a single threaded reference counting mechanism to release the data
%feature("ref", noblock=1) ma::Node {_ma_refcount_incr($this);};
%feature("unref", noblock=1) ma::Node {_ma_refcount_decr($this);};

#if defined(SWIGMATLAB)
%include "base_matlab.i"
#endif

%include "../include/openma/base/enums.h"

%include "base/any.i"
%include "base/object.i"
%include "base/node.i"
%include "base/event.i"
%include "base/subject.i"
%include "base/timesequence.i"
%include "base/trial.i"