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

#include "Stringy.h"

namespace vendor {
namespace acme {
namespace one {
namespace stringy {
namespace V1_0 {
namespace implementation {

// Methods from ::vendor::acme::one::stringy::V1_0::IStringy follow.
Return<void> Stringy::reverse(const hidl_string& inputText, reverse_cb _hidl_cb) {
    std::string  result;
    std::string  input = static_cast<std::string>(inputText);

    callCount++;

    for (int i = input.size(); i > 0; i--) {
        const char&  in = input[i - 1];
        result.push_back(in);
    }

    hidl_string  cbResult(result);
    _hidl_cb(cbResult);
    return Void();
}

Return<uint32_t> Stringy::hash(const hidl_string& inputText) {
    uint32_t     result = 0;
    std::string  input = static_cast<std::string>(inputText);

    callCount++;

    for (int i = 0; i < input.size(); i++) {
        result = (result << 8) ^ input[i];
    }

    return result;
}

Return<void> Stringy::split(const hidl_string& inputText, split_cb _hidl_cb) {
    std::vector<StringyChar>  content;
    std::string               input = static_cast<std::string>(inputText);

    callCount++;

    for (int i = 0; i < input.size(); i++) {
        content.push_back(static_cast<int8_t>(input[i]));
    }

    hidl_vec<StringyChar>  result = hidl_vec(content);
    _hidl_cb(result);
    return Void();
}

Return<void> Stringy::summarize(const hidl_string& inputText, summarize_cb _hidl_cb) {
    StringySummary  summary;

    callCount++;

    summary.charCount = inputText.size();
    summary.hash = hash(inputText);
    _hidl_cb(summary);
    return Void();
}

Return<void> Stringy::debug(const hidl_handle &handle, const hidl_vec<hidl_string> & /*options*/) {
    if (handle == nullptr || handle->numFds < 1 || handle->data[0] < 0) {
        return Void();
    }

    int fd = handle->data[0];
    dprintf(fd, "HIDL:\n");
    dprintf(fd, "  Call count: %d\n", callCount);
    fsync(fd);
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

}  // namespace implementation
}  // namespace V1_0
}  // namespace stringy
}  // namespace one
}  // namespace acme
}  // namespace vendor
