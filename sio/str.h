#ifndef SIO_STR_H
#define SIO_STR_H

#include <string>

#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_format.h"
#include "absl/meta/type_traits.h"

namespace sio {
using str = std::string;
using str_view = absl::string_view;
};

#endif
