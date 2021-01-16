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
using				std::map;
using				std::multimap;
using				std::unordered_map;
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
using 				std::ref;

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

// ---------------- Asynchronous

#include <shared_mutex>
#include <future>

using				std::mutex;
using				std::shared_mutex;
using				std::shared_lock;
using				std::unique_lock;

using				std::async;
using				std::launch;
using				std::future;
using				std::future_status;
using				std::promise;

namespace			this_thread = std::this_thread;

// ---------------- Time

#include <chrono>

namespace			chrono = std::chrono;

// ---------------- Other classes

#include <iterator>
#include <functional>
#include <optional>
#include <limits>

using				std::filesystem::path;
using				std::function;
using				std::optional;
using				std::nullopt;
using				std::numeric_limits;

// ---------------- Other functions

using				std::to_string;
using				std::filesystem::exists;
using				std::min;
using				std::max;
using				std::hash;