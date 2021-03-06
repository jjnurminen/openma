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

#include "hpfplugin.h"
#include "openma/io/enums.h"

#define _OPENMA_IO_HANDLER_DELSYS_HPF_FORMAT "delsys.hpf"

namespace ma
{
namespace io
{
  std::string HPFPlugin::name() const _OPENMA_NOEXCEPT
  {
    return "HPFPlugin";
  }
  
  std::vector<std::string> HPFPlugin::supportedFormats() const _OPENMA_NOEXCEPT
  {
    return {_OPENMA_IO_HANDLER_DELSYS_HPF_FORMAT};
  };

  Capability HPFPlugin::capabilities(const std::string& format) const _OPENMA_NOEXCEPT
  {
    if (format.compare(_OPENMA_IO_HANDLER_DELSYS_HPF_FORMAT) != 0)
      return Capability::None;
    return Capability::CanRead;
  };

  Signature HPFPlugin::detectSignature(const Device* const device, std::string* format) const _OPENMA_NOEXCEPT
  {
    Signature detected = Signature::Invalid;
    if ((detected = HPFHandler::verifySignature(device)) == Signature::Valid)
    {
      if (format != nullptr)
        *format = _OPENMA_IO_HANDLER_DELSYS_HPF_FORMAT;
    }
    return detected;
  };

  Handler* HPFPlugin::create(Device* device, const std::string& format)
  {
    OPENMA_UNUSED(format)
    Handler* handler = new HPFHandler;
    handler->setDevice(device);
    return handler;
  };
};
};