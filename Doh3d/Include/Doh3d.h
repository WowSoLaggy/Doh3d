#pragma once


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

#include "../Math.h"
#include "../Rect.h"
#include "../Matrix.h"
#include "../Vector2I.h"
#include "../Vector2F.h"

#include "../RenderMan.h"
#include "../StartupPars.h"
#include "../WinClass.h"
#include "../Drawer.h"
#include "../Camera.h"
#include "../Cursor.h"
#include "../MessagePeeker.h"
#include "../InputMan.h"
#include "../ResourceMan.h"
#include "../Screen.h"
#include "../Sprite.h"
#include "../ITreeItem.h"
#include "../IDrawable.h"
#include "../IUpdatable.h"
#include "../Viewport.h"
#include "../GuiList.h"
#include "../AnimationSet.h"
#include "../AnimationController.h"
#include "../Position2I.h"
#include "../Size2I.h"
#include "../IPositioned2I.h"
#include "../ITextured.h"
#include "../ISized2.h"
#include "../IInputHandler.h"
#include "../TextContainer.h"
#include "../IControlable.h"
#include "../Controller.h"
#include "../IMovable.h"
