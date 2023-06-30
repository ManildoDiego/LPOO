#pragma once

#include <string>

// struct anonimo de colores
struct {
	const std::string grey       = "\x1B[30m";
	const std::string red        = "\x1B[31m";
	const std::string green      = "\x1B[32m";
	const std::string yellow     = "\x1B[33m";
	const std::string blue       = "\x1B[34m";
	const std::string magenta    = "\x1B[35m";
	const std::string cyan       = "\x1B[36m";
	const std::string white      = "\x1B[37m";
	const std::string black      = "\x1B[30m";
	const std::string orange     = "\033[38;5;202m";

	const std::string black_bg   = "\x1B[40m";
	const std::string red_bg     = "\x1B[41m";
	const std::string green_bg   = "\x1B[42m";
	const std::string yellow_bg  = "\x1B[43m";
	const std::string blue_bg    = "\x1B[44m";
	const std::string magenta_bg = "\x1B[45m";
	const std::string cyan_bg    = "\x1B[46m";
	const std::string white_bg   = "\x1B[47m";
	const std::string reset_bg   = "\x1B[47m";
	
	const std::string underline  = "\033[4m";
	const std::string reset      = "\033[0m";
	const std::string bold       = "\033[1m";
} color;