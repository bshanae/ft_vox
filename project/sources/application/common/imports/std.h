#pragma once

#pragma region Meta

#include <type_traits>

using				std::is_same;
using				std::enable_if;
using				std::is_base_of;

#pragma endregion

#pragma region Containers

#include <array>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>

using				std::array;
using				std::vector;
using				std::list;
using				std::map;
using				std::queue;
using				std::stack;
using				std::multimap;
using				std::unordered_map;

using				std::erase;
using				std::erase_if;

#pragma endregion

#pragma region Pointers

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

#pragma endregion

#pragma region IO

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

#pragma endregion

#pragma region Asynchronous

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

#pragma endregion

#pragma region Time

#include <chrono>

namespace			chrono = std::chrono;

#pragma endregion

#pragma region Other classes

#include <iterator>
#include <functional>
#include <optional>
#include <limits>

using				std::filesystem::path;
using				std::function;
using				std::optional;
using				std::nullopt;
using				std::numeric_limits;
using				std::pair;

#pragma endregion

#pragma region Other functions

using				std::to_string;
using				std::filesystem::exists;
using				std::min;
using				std::max;
using				std::hash;

#pragma endregion