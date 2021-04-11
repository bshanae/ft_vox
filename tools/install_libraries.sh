#!/bin/bash

########################################################################################################################
# Constants
########################################################################################################################

REDIRECT_OUTPUT=1

RESET="\033[0m"
RED="\033[31m"
GREEN="\033[32m"

CURL_FLAGS="-Lf"

LIBRARIES="project/libraries"

########################################################################################################################
# Common
########################################################################################################################

function raise_error
{
	echo -e "${RED}Error : $1${RESET}"
	exit
}

function evaluate
{
	COMMAND="$1"
	OPTIONS=""

	if ((REDIRECT_OUTPUT)); then
		OPTIONS="> /dev/null 2>&1"
	fi

	eval "$COMMAND" "$OPTIONS"
}

########################################################################################################################
# IO
########################################################################################################################

function write
{
	echo -e "$1"
}

function write_new_line
{
	echo ""
}

function enter_folder
{
	cd "$1" > /dev/null 2>&1 || raise_error "Can't enter folder $1" "Can't download from URL ${URL}"
}

function log_start
{
	write "Started installing $1..."
}

function log_finish
{
	write "Successfully installed ${GREEN}$1${RESET}!"
}

function clean
{
	ARCHIVE="$1"
	CONTENT="$2"
	PROJECT="$3"

  	rm -f "$ARCHIVE"
	rm -rf "$CONTENT"
	rm -rf "$PROJECT"
}

########################################################################################################################
# Libraries
########################################################################################################################

function enter_libraries_folder
{
	mkdir -p "$LIBRARIES"
	enter_folder "$LIBRARIES"
}

function reset_libraries_folder
{
	rm -rf "$LIBRARIES"
}

########################################################################################################################
# GIT
########################################################################################################################

function download_from_git
{
	evaluate "git clone --recursive $1 $2"
}

########################################################################################################################
# GLFW
########################################################################################################################

function install_glfw
{
	GLFW_NAME="GLFW"
	GLFW_URL="https://github.com/glfw/glfw.git"
	GLFW_PROJECT="glfw"

	log_start "$GLFW_NAME"

	download_from_git "$GLFW_URL" "$GLFW_PROJECT"

	log_finish "$GLFW_NAME"
	write_new_line
}

########################################################################################################################
# GLAD
########################################################################################################################

function install_glad
{
	GLAD_NAME="GLAD"
	GLAD_URL="https://github.com/Dav1dde/glad.git"
	GLAD_PROJECT="glad"

	write "Installing ${GLAD_NAME}..."

	download_from_git "$GLAD_URL" "$GLAD_PROJECT"

	write "Building GLAD..."

	enter_folder  "$GLAD_PROJECT"

	evaluate "cmake ./"
	evaluate "make"

	enter_folder ..

	write "Successfully installed ${GREEN}${GLAD_NAME}${RESET}!"
	write_new_line
}

########################################################################################################################
# FastNoise
########################################################################################################################

function install_fast_noise
{
	FAST_NOISE_NAME="FastNoise"
	FAST_NOISE_URL="https://github.com/Auburn/FastNoise.git"
	FAST_NOISE_PROJECT="FastNoise"

	log_start "$FAST_NOISE_NAME"

	download_from_git "$FAST_NOISE_URL" "$FAST_NOISE_PROJECT"

	log_finish "$FAST_NOISE_NAME"
	write_new_line
}

########################################################################################################################
# GLM
########################################################################################################################

function install_glm
{
	GLM_NAME="GLM"
	GLM_URL="https://github.com/g-truc/glm.git"
	GLM_PROJECT="glm"

	log_start "$GLM_NAME"

	download_from_git "$GLM_URL" "$GLM_PROJECT"

	log_finish "$GLM_NAME"
	write_new_line
}

########################################################################################################################
# FreeType2
########################################################################################################################

function install_free_type
{
	FREE_TYPE_NAME="FreeType2"
	FREE_TYPE_URL="https://github.com/aseprite/freetype2.git"
	FREE_TYPE_PROJECT="freetype2"

	log_start "$FREE_TYPE_NAME"

	download_from_git "$FREE_TYPE_URL" "$FREE_TYPE_PROJECT"

	log_finish "$FREE_TYPE_NAME"
	write_new_line
}

########################################################################################################################
# STB
########################################################################################################################

function install_stb
{
	STB_NAME="STB"
	STB_URL="https://github.com/nothings/stb.git"
	STB_PROJECT="stb"

	log_start "$STB_NAME"

	download_from_git "$STB_URL" "$STB_PROJECT"

	log_finish "$STB_NAME"
	write_new_line
}

########################################################################################################################
# OpenCL
########################################################################################################################

function install_clhpp
{
	CLHPP_NAME="OpenCL-CLHPP"
	CLHPP_URL="https://github.com/KhronosGroup/OpenCL-CLHPP.git"
	CLHPP_PROJECT="clhpp"

	log_start "$CLHPP_NAME"

	download_from_git "$CLHPP_URL" "$CLHPP_PROJECT"

	log_finish "$CLHPP_NAME"
}

########################################################################################################################
# Main
########################################################################################################################

reset_libraries_folder
enter_libraries_folder

install_glfw
install_glad
install_fast_noise
install_glm
install_free_type
install_stb
install_clhpp