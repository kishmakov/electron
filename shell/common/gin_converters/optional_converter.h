// Copyright (c) 2023 Microsoft, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_COMMON_GIN_CONVERTERS_OPTIONAL_CONVERTER_H_
#define ELECTRON_SHELL_COMMON_GIN_CONVERTERS_OPTIONAL_CONVERTER_H_

#include <utility>

#include "gin/converter.h"
#include "third_party/abseil-cpp/absl/types/optional.h"

namespace gin {

template <typename T>
struct Converter<absl::optional<T>> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const absl::optional<T>& val) {
    if (val)
      return Converter<T>::ToV8(isolate, val.value());
    else
      return v8::Null(isolate);
  }
  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     absl::optional<T>* out) {
    T converted;
    if (Converter<T>::FromV8(isolate, val, &converted))
      out->emplace(std::move(converted));
    return true;
  }
};

}  // namespace gin

#endif  // ELECTRON_SHELL_COMMON_GIN_CONVERTERS_OPTIONAL_CONVERTER_H_
