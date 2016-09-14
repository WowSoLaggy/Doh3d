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

#include "Doh3d\ErrCodes3d.h"
using namespace Doh3d::Doh3dErrCodes;

#include "Doh3d\RenderMan.h"
#include "Doh3d\StartupPars.h"
#include "Doh3d\WinClass.h"
#include "Doh3d\Drawer.h"
#include "Doh3d\MessagePeeker.h"
#include "Doh3d\InputMan.h"
#include "Doh3d\ResourceMan.h"
#include "Doh3d\Cursor.h"
#include "Doh3d\Sprite.h"
#include "Doh3d\Matrix.h"


#endif // DOH3D_H
