#ifndef PRECOMPILED_HEADER_HPP
#define PRECOMPILED_HEADER_HPP

// SFML
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// Raspberry Pi
#ifdef SFML_SYSTEM_LINUX
	#ifdef __arm__
		#define SFML_SYSTEM_PI
	#endif
#endif // SFML SYSTEM_LINUX

// Typical stdafx.h
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>
#include <list>
#include <deque>
#include <memory>

// Additional C/C++ libs
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <sstream>
#include <iomanip>
#include <atomic>
#include <random>
#include <type_traits>
#include <exception>

// Windows
#ifdef SFML_SYSTEM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif // SFML_SYSTEM_WINDOWS

// Utils
//#include "Utility/Types.hpp" // Example

// Macros
#define _UNUSED(x) (void)(x)

#endif // PRECOMPILED_HEADER_HPP
