#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

// ---------------- Meta

using				std::is_same;
using 				std::enable_shared_from_this;

// ---------------- Containers

using				std::vector;
using				std::map;

// ---------------- Pointers

using 				std::shared_ptr;
using 				std::make_shared;
using 				std::unique_ptr;
using 				std::make_unique;

// ---------------- Other classes

using				std::cerr;
using				std::cout;
using				std::endl;
using				std::string;
using				std::filesystem::path;
using				std::ifstream;
using				std::stringstream;

// ---------------- Other functions

using				std::filesystem::exists;
