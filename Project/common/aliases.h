#pragma once

#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

// ---------------- Meta

using				std::is_same;
using 				std::enable_shared_from_this;

// ---------------- Containers

using				std::vector;

// ---------------- Pointers

using 				std::shared_ptr;
using 				std::make_shared;

// ---------------- Other classes

using				std::string;
using				std::filesystem::path;
using				std::ifstream;
using				std::stringstream;

// ---------------- Other functions

using				std::filesystem::exists;
