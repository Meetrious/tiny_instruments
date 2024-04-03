#ifndef ESC_CODES_
#define ESC_CODES_

const char
  *resetfont = "\033[m",

	*underline = "\033[4m", *underline2 = "\033[21m", *cross = "\033[9m",
	*bold = "\033[1m", *italic = "\033[3m", *gray = "\033[2m", *invisible = "\033[8m",

	*red = "\033[91m", *green = "\033[92m",
	*yellow = "\033[93m", *cyan = "\033[96m",

	*HLBlack = "\033[40m",
	*HLRed = "\033[41m",
	*HLGreen = "\033[42m",
	*HLYellow = "\033[43m",

	cls = "\033[2J",
	resetpos = "\x1b[0;0H";

#endif  // ESC_CODES_

