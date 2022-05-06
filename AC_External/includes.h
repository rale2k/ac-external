#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <tlhelp32.h>   
#include <string>
#include <vector>
#include <cstdint>
#include <thread>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")
#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")

#include "main.h"
#include "utils/structs.h"
#include "extinterface.h"
#include "utils/maths.h"
#include "utils/utils.h"
#include "interfaces.h"
#include "overlay/paint.h"
#include "overlay/overlay.h"
#include "features/features.h"

// extinterface macros
#define GET(obj, var) obj.Get(&obj.proxy->var)
#define SET(obj, var, val) obj.Set(&obj.proxy->var, val)
