#pragma once

#ifndef DOH3D_H
#define DOH3D_H


// System

#define NOMINMAX
#include <Windows.h>
#include <string>
#include <functional>
#include <algorithm>
#include <regex>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <vector>


// DirectX

#define DIRECTINPUT_VERSION 0x0800
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>


// 3rd party

#ifdef DOH3D_NOLOG
	#define LOG(x)
	#define echo(x)
#else
	#include <Log.h>
#endif // DOH3D_NOLOG

#include <Timer.h>


// Doh3d

#include "../RenderMan.h"
#include "../StartupPars.h"
#include "../WinClass.h"
#include "../Drawer.h"
#include "../MessagePeeker.h"
#include "../InputMan.h"
#include "../ResourceMan.h"
#include "../Screen.h"
#include "../Cursor.h"
#include "../Sprite.h"
#include "../Matrix.h"
#include "../ITreeItem.h"
#include "../IDrawableTreeItem.h"
#include "../IUpdatableTreeItem.h"
#include "../Viewport.h"
#include "../GuiList.h"
#include "../AnimationSet.h"
#include "../AnimationController.h"
#include "../Rect.h"
#include "../Position2.h"
#include "../Size2.h"
#include "../IPositioned.h"
#include "../ITextured.h"
#include "../ISized.h"


#endif // DOH3D_H
