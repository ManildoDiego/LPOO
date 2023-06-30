#pragma once

// struct anonimo de colores
struct {
	const char* grey       = "\x1B[30m";
	const char* red        = "\x1B[31m";
	const char* green      = "\x1B[32m";
	const char* yellow     = "\x1B[33m";
	const char* blue       = "\x1B[34m";
	const char* magenta    = "\x1B[35m";
	const char* cyan       = "\x1B[36m";
	const char* white      = "\x1B[37m";
	const char* black      = "\x1B[30m";
	const char* orange     = "\033[38;5;202m";

	const char* black_bg   = "\x1B[40m";
	const char* red_bg     = "\x1B[41m";
	const char* green_bg   = "\x1B[42m";
	const char* yellow_bg  = "\x1B[43m";
	const char* blue_bg    = "\x1B[44m";
	const char* magenta_bg = "\x1B[45m";
	const char* cyan_bg    = "\x1B[46m";
	const char* white_bg   = "\x1B[47m";
	const char* reset_bg   = "\x1B[47m";
	
	const char* underline  = "\033[4m";
	const char* reset      = "\033[0m";
	const char* bold       = "\033[1m";
} color;