#include "PrecompiledHeader.h"
//#include "GButton.h"
//
//#include "ResourceMan.h"
//
//
//namespace Doh3d
//{
//
//	GButton::GButton(float pPosX, float pPosY, float pSizeX, float pSizeY,
//					 const std::string& pTexNameNormal, const std::string& pTexNamePressed,
//					 const std::string& pTexNameSelected, const std::string& pTexNameDisabled)
//	{
//		LOG("GButton::GButton()");
//
//		d_position.x = roundf(pPosX);
//		d_position.y = roundf(pPosY);
//		d_position.z = 0;
//
//		if (!setSize(pSizeX, pSizeY))
//			echo("ERROR: Can't set size.");
//
//		d_texNameNormal = pTexNameNormal;
//		d_texNamePressed = pTexNamePressed;
//		d_texNameSelected = pTexNameSelected;
//		d_texNameDisabled = pTexNameDisabled;
//
//		d_tiNormal = 0;
//		d_tiPressed = 0;
//		d_tiSelected = 0;
//		d_tiDisabled = 0;
//
//		d_state = GStates::Normal;
//
//		onClickEvent = nullptr;
//
//		d_textContainer.setTextAlign(TextAlign::Center);
//	}
//
//	GButton::~GButton()
//	{
//	}
//
//
//  bool GButton::load()
//	{
//		LOG("GButton::load()");
//
//		if (!ResourceMan::getTi(d_texNameNormal, d_tiNormal))
//		{
//			echo("ERROR: Can't get TI for GButton (id: ", d_id, "): \"", d_texNameNormal, "\".");
//			return false;
//		}
//
//		if (!ResourceMan::getTi(d_texNamePressed, d_tiPressed))
//		{
//			echo("ERROR: Can't get TI for GButton (id: ", d_id, "): \"", d_texNamePressed, "\".");
//			return false;
//		}
//
//		if (!ResourceMan::getTi(d_texNameSelected, d_tiSelected))
//		{
//			echo("ERROR: Can't get TI for GButton (id: ", d_id, "): \"", d_texNameSelected, "\".");
//			return false;
//		}
//
//		if (!ResourceMan::getTi(d_texNameDisabled, d_tiDisabled))
//		{
//			echo("ERROR: Can't get TI for GButton (id: ", d_id, "): \"", d_texNameDisabled, "\".");
//			return false;
//		}
//
//		if (!updateTransformMatrix())
//		{
//			echo("ERROR: Can't update TransformMatrix for GButton (id: ", d_id, ").");
//			return false;
//		}
//
//		if (!d_textContainer.load())
//		{
//			echo("ERROR: Can't load TextContainer for GButton (id: ", d_id, ").");
//			return false;
//		}
//
//		if (!d_textContainer.setBasisPosition(D3DXVECTOR3(getSize().x / 2, getSize().y / 2, 0)))
//		{
//			echo("ERROR: Can't set basis for TextContainer.");
//			return false;
//		}
//
//		return true;
//	}
//
//  bool GButton::unload()
//	{
//		LOG("GButton::unload()");
//
//		if (!d_textContainer.unload())
//		{
//			echo("ERROR: Can't unload TextContainer for GButton (id: ", d_id, ").");
//			return false;
//		}
//
//		return true;
//	}
//
//  bool GButton::draw(Sprite& pSprite) const
//	{
//		LOG("GButton::draw()");
//		int hRes;
//
//		pSprite.get()->SetTransform(&d_transformMatrix);
//
//		switch (d_state)
//		{
//		case GStates::Pressed:
//			hRes = pSprite.get()->Draw(ResourceMan::getTexture(d_tiPressed).get(), &ResourceMan::getTexture(d_tiPressed).getFrame(0), 0, &d_position, D3DCOLOR_ARGB(255, 255, 255, 255));
//			break;
//		case GStates::Selected:
//			hRes = pSprite.get()->Draw(ResourceMan::getTexture(d_tiSelected).get(), &ResourceMan::getTexture(d_tiSelected).getFrame(0), 0, &d_position, D3DCOLOR_ARGB(255, 255, 255, 255));
//			break;
//		case GStates::Disabled:
//			hRes = pSprite.get()->Draw(ResourceMan::getTexture(d_tiDisabled).get(), &ResourceMan::getTexture(d_tiDisabled).getFrame(0), 0, &d_position, D3DCOLOR_ARGB(255, 255, 255, 255));
//			break;
//		default:
//			hRes = pSprite.get()->Draw(ResourceMan::getTexture(d_tiNormal).get(), &ResourceMan::getTexture(d_tiNormal).getFrame(0), 0, &d_position, D3DCOLOR_ARGB(255, 255, 255, 255));
//			break;
//		}
//
//		if (hRes != S_OK)
//		{
//			echo("ERROR: Can't draw sprite.");
//			return false;
//		}
//
//		if (d_textContainer.hasText())
//		{
//			hRes = pSprite.get()->Draw(d_textContainer.getTexture(), 0, 0, &(d_position + d_textContainer.getPosition()), D3DCOLOR_ARGB(255, 255, 255, 255));
//			if (hRes != S_OK)
//			{
//				echo("ERROR: Can't draw text.");
//				return false;
//			}
//		}
//
//		return true;
//	}
//
//	D3DXVECTOR2 GButton::getOriginalSize() const
//	{
//		return ResourceMan::getTexture(d_tiNormal).getSize();
//	}
//
//  bool GButton::onMouseMove(bool& pHandled)
//	{
//		LOG("GButton::onMouseMove()");
//
//		if (!GBase::onMouseMove(pHandled))
//		{
//			echo("ERROR: Error occurred while GBase::onMouseMove().");
//			return false;
//		}
//
//		if (d_state == GStates::Disabled)
//			return true;
//
//		if (containsPoint(InputMan::getCursorPosition()))
//		{
//			if (d_state == GStates::Normal)
//				d_state = GStates::Selected;
//		}
//		else
//			d_state = GStates::Normal;
//
//		return true;
//	}
//
//  bool GButton::onMouseDown(bool& pHandled, int pButton)
//	{
//		LOG("GButton::onMouseDown()");
//
//		if (!GBase::onMouseDown(pHandled, pButton))
//		{
//			echo("ERROR: Error occurred while GBase::onMouseDown().");
//			return false;
//		}
//
//		if (d_state == GStates::Disabled)
//			return true;
//
//		if (pButton != MBUTTON_LEFT)
//			return true;
//
//		if (containsPoint(InputMan::getCursorPosition()))
//			d_state = GStates::Pressed;
//		else
//			d_state = GStates::Normal;
//
//		return true;
//	}
//
//  bool GButton::onMouseUp(bool& pHandled, int pButton)
//	{
//		LOG("GButton::onMouseUp()");
//
//		if (pButton != MBUTTON_LEFT)
//		{
//			pHandled = false;
//			return true;
//		}
//
//		if (!GBase::onMouseUp(pHandled, pButton))
//		{
//			echo("ERROR: Error occurred while GBase::onMouseUp().");
//			return false;
//		}
//
//		if (d_state == GStates::Disabled)
//			return true;
//
//		if (pButton != MBUTTON_LEFT)
//			return true;
//
//		if (containsPoint(InputMan::getCursorPosition()))
//		{
//			if (d_state == GStates::Pressed)
//			{
//				if (!click())
//				{
//					echo("ERROR: Error occurred while button click.");
//					return false;
//				}
//			}
//
//			d_state = GStates::Selected;
//		}
//		else
//			d_state = GStates::Normal;
//
//		return true;
//	}
//
//  bool GButton::setOnClickEvent(std::function<void()> pEvent)
//	{
//		onClickEvent = pEvent;
//		return true;
//	}
//
//  bool GButton::click()
//	{
//		LOG("GButton::click()");
//		
//		if ((d_state == GStates::Disabled) || (!d_isVisible))
//			return true;
//
//		if (onClickEvent != nullptr)
//			onClickEvent();
//
//		return true;
//	}
//
//
//  bool GButton::setText(const std::string& pText)
//	{
//		LOG("GButton::setText()");
//
//		if (!d_textContainer.setText(pText))
//		{
//			echo("ERROR: Can't set text to TextContainer.");
//			return false;
//		}
//
//		return true;
//	}
//
//  bool GButton::setFont(const std::string& pFontName)
//	{
//		LOG("GButton::setFont()");
//
//		if (!d_textContainer.setFont(pFontName))
//		{
//			echo("ERROR: Can't set font for GButton (id: ", d_id, ").");
//			return false;
//		}
//
//		return true;
//	}
//
//} // ns Doh3d
