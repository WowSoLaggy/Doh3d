//#include "Doh3d.h"
//#include "GText.h"
//
//
//namespace Doh3d
//{
//
//	GText::GText(float pPosX, float pPosY, const std::string& pText, const std::string& pFontName)
//	{
//		d_position.x = roundf(pPosX);
//		d_position.y = roundf(pPosY);
//		d_position.z = 0;
//		setSize(0, 0);
//		setText(pText);
//		setFont(pFontName);
//		d_textContainer.setTextAlign(TextAlign::Left);
//	}
//
//	GText::~GText()
//	{
//	}
//
//
//  bool GText::load()
//	{
//		LOG("GText::load()");
//
//		if (!d_textContainer.load())
//		{
//			echo("ERROR: Can't load TextContainer for GText (id: ", d_id, ").");
//			return false;
//		}
//
//		if (!updateTransformMatrix())
//		{
//			echo("ERROR: Can't update TransformMatrix for GText (id: ", d_id, ").");
//			return false;
//		}
//
//		if (!setSize((float)d_textContainer.textWidth(), (float)d_textContainer.textHeight()))
//		{
//			echo("ERROR: Can't set size for GText (id: ", d_id, ").");
//			return false;
//		}
//
//		return true;
//	}
//
//  bool GText::unload()
//	{
//		LOG("GText::unload()");
//
//		if (!d_textContainer.unload())
//		{
//			echo("ERROR: Can't unload TextContainer for GText (id: ", d_id, ").");
//			return false;
//		}
//
//		return true;
//	}
//
//  bool GText::draw(Sprite& pSprite) const
//	{
//		LOG("GText::draw()");
//		int hRes;
//
//		pSprite.get()->SetTransform(&d_transformMatrix);
//		if (d_textContainer.hasText())
//		{
//			hRes = pSprite.get()->Draw(d_textContainer.getTexture(), 0, 0, &(d_position + d_textContainer.getPosition()), D3DCOLOR_ARGB(255, 255, 255, 255));
//			if (hRes != S_OK)
//			{
//				echo("ERROR: Can't draw Text for GText (id: ", d_id, ").");
//				return false;
//			}
//		}
//
//		return true;
//	}
//
//	D3DXVECTOR2 GText::getOriginalSize() const
//	{
//		return getSize();
//	}
//
//  bool GText::setText(const std::string& pText)
//	{
//		LOG("GText::setText()");
//
//		if (!d_textContainer.setText(pText))
//		{
//			echo("ERROR: Can't set text to TextContainer.");
//			return false;
//		}
//
//		if (!setSize((float)d_textContainer.textWidth(), (float)d_textContainer.textHeight()))
//		{
//			echo("ERROR: Can't set size for GText (id: ", d_id, ").");
//			return false;
//		}
//
//		return true;
//	}
//
//  bool GText::setFont(const std::string& pFontName)
//	{
//		LOG("GText::setFont()");
//
//		if (!d_textContainer.setFont(pFontName))
//		{
//			echo("ERROR: Can't set font for GText (id: ", d_id, ").");
//			return false;
//		}
//
//		if (!setSize((float)d_textContainer.textWidth(), (float)d_textContainer.textHeight()))
//		{
//			echo("ERROR: Can't set size for GText (id: ", d_id, ").");
//			return false;
//		}
//
//		return true;
//	}
//
//
//  bool GText::setSize(float pWidth, float pHeight)
//	{
//		LOG("GText::setSize()");
//
//		if (!GBase::setSize(pWidth, pHeight))
//		{
//			echo("ERROR: Can't set size for GText (id: ", d_id, ").");
//			return false;
//		}
//
//		if (!d_textContainer.setBasisPosition(D3DXVECTOR3(0, pHeight / 2, 0)))
//		{
//			echo("ERROR: Can't set basis for TextContainer.");
//			return false;
//		}
//
//		return true;
//	}
//
//  bool GText::setSize(const D3DXVECTOR2& pSize)
//	{
//		return setSize(pSize.x, pSize.y);
//	}
//
//} // ns Doh3d
