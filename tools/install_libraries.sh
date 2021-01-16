#!/bin/bash

########################################################################################################################
# Common
########################################################################################################################

REDIRECT_OUTPUT=1

RESET="\033[0m"
RED="\033[31m"
GREEN="\033[32m"

CURL_FLAGS="-Lf"

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

function enter_libraries_folder
{
	LIBRARIES="project/libraries"

	mkdir -p "$LIBRARIES"
	enter_folder "$LIBRARIES"
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

function download
{
	NAME="$1"
	URL="$2"
	FILE="$3"

	write "Downloading $1..."

	evaluate "curl $CURL_FLAGS $URL -o $FILE"

	if [ "$?" -ne 0 ]; then
    	raise_error "Can't download from URL ${URL}"
	fi
}

function unpack
{
	NAME="$1"
	ARCHIVE="$2"
	CONTENT="$3"

	write "Unpacking $NAME..."

  	tar -zxf "$ARCHIVE" "$CONTENT"
	rm -f "$ARCHIVE"
}

function rename
{
	NAME="$1"
	FROM="$2"
	TO="$3"

	write "Moving $NAME..."

	rm -rf "$TO"
	mv "$FROM" "$TO" || raise_error "Can't move $FROM to $TO"
}

########################################################################################################################
# GLFW
########################################################################################################################

function install_glfw
{
	GLFW_NAME="GLFW"
	GLFW_URL="https://github.com/glfw/glfw/archive/3.3.2.tar.gz"
	GLFW_ARCHIVE="glfw.tar.gz"
	GLFW_ARCHIVE_CONTENT="glfw-3.3.2"
	GLFW_PROJECT="glfw"

	log_start "$GLFW_NAME"

	clean "$GLFW_ARCHIVE" "$GLFW_ARCHIVE_CONTENT" "$GLFW_PROJECT"
	download "$GLFW_NAME" "$GLFW_URL" "$GLFW_ARCHIVE"
	unpack "$GLFW_NAME" "$GLFW_ARCHIVE" "$GLFW_ARCHIVE_CONTENT"
	rename "$GLFW_NAME" "$GLFW_ARCHIVE_CONTENT" "$GLFW_PROJECT"

	log_finish "$GLFW_NAME"
	write_new_line
}

########################################################################################################################
# GLAD
########################################################################################################################

function install_glad
{
	GLAD_NAME="GLAD"
	GLAD_URL="https://github.com/Dav1dde/glad/archive/v0.1.34.tar.gz"
	GLAD_ARCHIVE="glad.tar.gz"
	GLAD_ARCHIVE_CONTENT="glad-0.1.34"
	GLAD_PROJECT="glad"
	GLAD_BUILD="build"

	write "Installing GLAD..."

	clean "$GLAD_ARCHIVE" "$GLAD_ARCHIVE_CONTENT" "$GLAD_PROJECT"
	download "$GLAD_NAME" "$GLAD_URL" "$GLAD_ARCHIVE"
	unpack "$GLAD_NAME" "$GLAD_ARCHIVE" "$GLAD_ARCHIVE_CONTENT"
	rename "$GLAD_NAME" "$GLAD_ARCHIVE_CONTENT" "$GLAD_PROJECT"

	write "Building GLAD..."

	enter_folder  "$GLAD_PROJECT"
	mkdir "$GLAD_BUILD"
	enter_folder  "$GLAD_BUILD"

	evaluate "cmake .."
	evaluate "make"

	enter_folder ../..

	write "Successfully installed ${GREEN}GLAD${RESET}!"
	write_new_line
}

########################################################################################################################
# FastNoise
########################################################################################################################

function install_fast_noise
{
	FAST_NOISE_NAME="FastNoise"
	FAST_NOISE_URL="https://github.com/Auburn/FastNoise/archive/v1.0.1.tar.gz"
	FAST_NOISE_ARCHIVE="FastNoise.tar.gz"
	FAST_NOISE_ARCHIVE_CONTENT="FastNoise-1.0.1"
	FAST_NOISE_PROJECT="FastNoise"

	log_start "$FAST_NOISE_NAME"

	clean "$FAST_NOISE_ARCHIVE" "$FAST_NOISE_ARCHIVE_CONTENT" "$FAST_NOISE_PROJECT"
	download "$FAST_NOISE_NAME" "$FAST_NOISE_URL" "$FAST_NOISE_ARCHIVE"
	unpack "$FAST_NOISE_NAME" "$FAST_NOISE_ARCHIVE" "$FAST_NOISE_ARCHIVE_CONTENT"
	rename "$FAST_NOISE_NAME" "$FAST_NOISE_ARCHIVE_CONTENT" "$FAST_NOISE_PROJECT"

	log_finish "$FAST_NOISE_NAME"
	write_new_line
}

########################################################################################################################
# GLM
########################################################################################################################

function install_glm
{
	GLM_NAME="GLM"
	GLM_URL="https://github.com/g-truc/glm/archive/0.9.9.8.tar.gz"
	GLM_ARCHIVE="glm.tar.gz"
	GLM_ARCHIVE_CONTENT="glm-0.9.9.8"
	GLM_PROJECT="glm"

	log_start "$GLM_NAME"

	clean "$GLM_ARCHIVE" "$GLM_ARCHIVE_CONTENT" "$GLM_PROJECT"
	download "$GLM_NAME" "$GLM_URL" "$GLM_ARCHIVE"
	unpack "$GLM_NAME" "$GLM_ARCHIVE" "$GLM_ARCHIVE_CONTENT"
	rename "$GLM_NAME" "$GLM_ARCHIVE_CONTENT" "$GLM_PROJECT"

	log_finish "$GLM_NAME"
	write_new_line
}

########################################################################################################################
# FreeType2
########################################################################################################################

function install_free_type
{
	FREE_TYPE_NAME="FreeType2"
	FREE_TYPE_URL="https://github.com/aseprite/freetype2/archive/VER-2-10-0.tar.gz"
	FREE_TYPE_ARCHIVE="FreeType2.tar.gz"
	FREE_TYPE_ARCHIVE_CONTENT="freetype2-VER-2-10-0"
	FREE_TYPE_PROJECT="freetype2"

	log_start "$FREE_TYPE_NAME"

	clean "$FREE_TYPE_ARCHIVE" "$FREE_TYPE_ARCHIVE_CONTENT" "$FREE_TYPE_PROJECT"
	download "$FREE_TYPE_NAME" "$FREE_TYPE_URL" "$FREE_TYPE_ARCHIVE"
	unpack "$FREE_TYPE_NAME" "$FREE_TYPE_ARCHIVE" "$FREE_TYPE_ARCHIVE_CONTENT"
	rename "$FREE_TYPE_NAME" "$FREE_TYPE_ARCHIVE_CONTENT" "$FREE_TYPE_PROJECT"

	log_finish "$FREE_TYPE_NAME"
	write_new_line
}

########################################################################################################################
# FreeType2
########################################################################################################################

function install_stb
{
	STB_NAME="STB"
	STB_URL="https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"
	STB_PROJECT="stb"
	STB_FILE="stb_image.h"

	log_start "$STB_NAME"

	rm -rf "$STB_PROJECT"
	download "$STB_NAME" "$STB_URL" "$STB_FILE"

	mkdir "$STB_PROJECT"
	mv "$STB_FILE" "$STB_PROJECT"/"$STB_FILE"

	log_finish "$STB_NAME"
}

########################################################################################################################
# Main
########################################################################################################################

enter_libraries_folder

install_glfw
#install_glad
#install_fast_noise
#install_glm
#install_free_type
#install_stb