#pragma once

#ifndef INC_DOH3D_MESSAGEPEEKER_H
#define INC_DOH3D_MESSAGEPEEKER_H


namespace Doh3d
{

	// Peeks and translates the windows messages.
	// Returns true if the WM_QUIT message aquired
	bool WinPeekExit();

} // ns Doh3d


#endif // INC_DOH3D_MESSAGEPEEKER_H
