#pragma once

// ---------------- Meta

#include <type_traits>

using				std::is_same;

// ---------------- Containers

#include <map>
#include <array>
#include <vector>

using				std::vector;
using				std::array;

// ---------------- Pointers

#include <memory>

using 				std::shared_ptr;
using 				std::make_shared;
using 				std::unique_ptr;
using 				std::make_unique;
using 				std::enable_shared_from_this;

// ---------------- Other classes

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iterator>

using				std::cerr;
using				std::cout;
using				std::endl;
using				std::string;
using				std::filesystem::path;
using				std::ifstream;
using				std::stringstream;
using				std::input_iterator_tag;

// ---------------- Other functions

using				std::to_string;
using				std::filesystem::exists;
