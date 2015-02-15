// Copyright 2010-2015, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef MOZC_CONVERTER_CONNECTOR_BASE_H_
#define MOZC_CONVERTER_CONNECTOR_BASE_H_

#include <vector>

#include "base/port.h"
#include "base/scoped_ptr.h"
#include "converter/connector_interface.h"

namespace mozc {

class DataManagerInterface;

// TODO(noriyukit): Rename this to Connector as no class inherits this class.
class ConnectorBase : public ConnectorInterface {
 public:
  static ConnectorBase *CreateFromDataManager(
      const DataManagerInterface &data_manager);

  ConnectorBase(const char *connection_data, size_t connection_size,
                int cache_size);
  virtual ~ConnectorBase();

  virtual int GetTransitionCost(uint16 rid, uint16 lid) const;
  virtual int GetResolution() const;

  void ClearCache();

 private:
  class Row;

  int LookupCost(uint16 rid, uint16 lid) const;

  vector<Row *> rows_;
  const uint16 *default_cost_;
  int resolution_;

  const int cache_size_;
  const uint32 cache_hash_mask_;
  mutable scoped_ptr<uint32[]> cache_key_;
  mutable scoped_ptr<int[]> cache_value_;

  DISALLOW_COPY_AND_ASSIGN(ConnectorBase);
};

}  // namespace mozc

#endif  // MOZC_CONVERTER_CONNECTOR_BASE_H_
