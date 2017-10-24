#pragma once

#include <cstddef>
#include <limits>
#include <string>
#include <utility>

namespace specops {

using identifier = int;
using count = int;
using hash_type = std::size_t;
using tenure_type = std::size_t;

using timestamp = long;
const timestamp timestamp_min = 0;
const timestamp timestamp_max = std::numeric_limits<timestamp>::max();
using timerange = long;

using score = long;
const score score_max = std::numeric_limits<score>::max();

using partid = std::shared_ptr<std::string>;

using rpm = int;

}
