#pragma once

#ifndef DOH3D_H
#define DOH3D_H


// System

#define NOMINMAX
#include <Windows.h>
#include <string>
#include <functional>
#include <algorithm>


// DirectX

#define DIRECTINPUT_VERSION 0x0800
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>


// Doh3d

#ifdef DOH3D_NOLOG
	#define LOG(x)
	#define echo(x)
#else
	#include "Log.h"
#endif // DOH3D_NOLOG

#include "..\ErrCodes3d.h"
using namespace Doh3d::Doh3dErrCodes;

#include "..\RenderMan.h"
#include "..\StartupPars.h"
#include "..\WinClass.h"
#include "..\Drawer.h"
#include "..\MessagePeeker.h"
#include "..\InputMan.h"
#include "..\ResourceMan.h"
#include "..\Cursor.h"
#include "..\Sprite.h"
#include "..\Matrix.h"


#endif // DOH3D_H
