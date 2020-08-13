#pragma once

// ---------------- Meta

#include <type_traits>

using				std::is_same;
using				std::enable_if;
using				std::is_base_of;

// ---------------- Containers

#include <map>
#include <array>
#include <vector>
#include <queue>
#include <unordered_map>

using				std::vector;
using				std::array;
using				std::unordered_map;
using				std::multimap;
using				std::queue;
using				std::pair;

// ---------------- Pointers

#include <memory>

using 				std::shared_ptr;
using 				std::make_shared;
using 				std::unique_ptr;
using 				std::make_unique;
using 				std::static_pointer_cast;
using 				std::dynamic_pointer_cast;
using 				std::enable_shared_from_this;
using 				std::addressof;

// ---------------- IO

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using				std::cerr;
using				std::cout;
using				std::endl;
using				std::string;
using				std::istream;
using				std::ostream;
using				std::fstream;
using				std::ifstream;
using				std::ofstream;
using				std::stringstream;
using				std::ios;

// ---------------- Other classes

#include <iterator>
#include <functional>
#include <optional>
#include <limits>

using				std::filesystem::path;
using				std::input_iterator_tag;
using				std::function;
using				std::optional;
using				std::numeric_limits;

// ---------------- Other functions

using				std::to_string;
using				std::filesystem::exists;
using				std::min;
using				std::max;
using				std::hash;