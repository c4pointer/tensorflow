/* Copyright 2024 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "xla/service/gpu/nccl_clique_key.h"

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/types/span.h"
#include "xla/service/global_device_id.h"

namespace xla::gpu {

//===----------------------------------------------------------------------===//
// NcclCliqueKey
//===----------------------------------------------------------------------===//

NcclCliqueKey::NcclCliqueKey(std::vector<GlobalDeviceId> devices,
                             int64_t stream_id)
    : devices_(std::move(devices)), stream_id_(stream_id) {}

absl::Span<const GlobalDeviceId> NcclCliqueKey::devices() const {
  return devices_;
}

std::string NcclCliqueKey::ToString() const {
  return absl::StrCat("stream[", stream_id_, "]",
                      GlobalDeviceIdsToString(devices_));
}

bool operator==(const NcclCliqueKey& a, const NcclCliqueKey& b) {
  return a.devices_ == b.devices_ && a.stream_id_ == b.stream_id_;
}

}  // namespace xla::gpu
