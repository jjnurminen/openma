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

#ifndef __openma_body_dumasmcconvilleyoungtable_h
#define __openma_body_dumasmcconvilleyoungtable_h

#include "openma/body_export.h"
#include "openma/body/inertialparametersestimator.h"
#include "openma/base/macros.h" // _OPENMA_NOEXCEPT

namespace ma
{
namespace body
{
  class OPENMA_BODY_EXPORT DumasMcConvilleYoungTable : public InertialParametersEstimator
  {
    OPENMA_DECLARE_NODEID(DumasMcConvilleYoungTable, InertialParametersEstimator)
        
  public:
    DumasMcConvilleYoungTable(Node* parent = nullptr);
    ~DumasMcConvilleYoungTable() _OPENMA_NOEXCEPT;
    
    DumasMcConvilleYoungTable(const DumasMcConvilleYoungTable& ) = delete;
    DumasMcConvilleYoungTable(DumasMcConvilleYoungTable&& ) _OPENMA_NOEXCEPT = delete;
    DumasMcConvilleYoungTable& operator=(const DumasMcConvilleYoungTable& ) = delete;
    DumasMcConvilleYoungTable& operator=(DumasMcConvilleYoungTable&& ) _OPENMA_NOEXCEPT = delete;
    
    virtual bool run(Node* inout) final;
  };
};
};

OPENMA_EXPORT_STATIC_TYPEID(ma::body::DumasMcConvilleYoungTable, OPENMA_BODY_EXPORT);

#endif // __openma_body_dumasmcconvilleyoungtable_h