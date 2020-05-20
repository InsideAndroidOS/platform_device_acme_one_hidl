/*
 * Copyright (C) 2020 Larry Schiefer and Blake Meike
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <vendor/acme/one/stringy/1.0/IStringy.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace vendor {
namespace acme {
namespace one {
namespace stringy {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct Stringy : public IStringy {
    // Methods from ::vendor::acme::one::stringy::V1_0::IStringy follow.
    Return<void> reverse(const hidl_string& inputText, reverse_cb _hidl_cb) override;
    Return<uint32_t> hash(const hidl_string& inputText) override;
    Return<void> split(const hidl_string& inputText, split_cb _hidl_cb) override;
    Return<void> summarize(const hidl_string& inputText, summarize_cb _hidl_cb) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    Return<void> debug(const hidl_handle &handle, const hidl_vec<hidl_string> &options) override;

private:
    int32_t callCount;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace stringy
}  // namespace one
}  // namespace acme
}  // namespace vendor
