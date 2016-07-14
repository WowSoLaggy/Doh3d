#pragma once

#ifndef DOH3D_H
#define DOH3D_H


// System

#define NOMINMAX
#include <Windows.h>
#include <string>


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

#include "Doh3d\ErrCodes.h"
#include "Doh3d\RenderMan.h"
#include "Doh3d\StartupPars.h"
#include "Doh3d\WinClasReg.h"


#endif // DOH3D_H
