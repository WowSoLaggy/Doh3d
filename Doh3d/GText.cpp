#include "Doh3d.h"
#include "GText.h"


namespace Doh3d
{

	GText::GText(float pPosX, float pPosY, const std::string& pText)
	{
		m_position.x = roundf(pPosX);
		m_position.y = roundf(pPosY);
		m_position.z = 0;
		m_size.x = 0;
		m_size.y = 0;
		SetText(pText);
	}

	GText::~GText()
	{
	}


	ErrCode3d GText::Load()
	{
		LOG("GText::Load()");
		ErrCode3d err;

		err = UpdateTransformMatrix();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't update TransformMatrix for GText (id: ", m_id, ").");
			return err;
		}

		err = m_text.Load();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't load Text for GText (id: ", m_id, ").");
			return err;
		}
		m_positionText.x = roundf(m_position.x + (m_size.x - m_text.Width()) / 2);
		m_positionText.y = roundf(m_position.y + (m_size.y - m_text.Height()) / 2);

		return err3d_noErr;
	}

	ErrCode3d GText::Unload()
	{
		LOG("GText::Unload()");
		ErrCode3d err;

		err = m_text.Unload();
		if (err != err3d_noErr)
		{
			echo("ERROR: Can't unload Text for GText (id: ", m_id, ").");
			return err;
		}

		return err3d_noErr;
	}

	ErrCode3d GText::Draw(LPD3DXSPRITE pSprite)
	{
		LOG("GText::Draw()");
		int hRes;

		pSprite->SetTransform(&m_transformMatrix);
		if (m_text.IsText())
		{
			hRes = pSprite->Draw(m_text.GetTexture(), 0, 0, &m_positionText, D3DCOLOR_ARGB(255, 255, 255, 255));
			if (hRes != S_OK)
			{
				echo("ERROR: Can't draw Text for GText (id: ", m_id, ").");
				return err3d_cantDrawText;
			}
		}

		return err3d_noErr;
	}

	D3DXVECTOR2 GText::GetOriginalSize()
	{
		return D3DXVECTOR2((float)m_text.Width(), (float)m_text.Height());
	}

	ErrCode3d GText::SetText(const std::string& pText)
	{
		m_text.SetText(pText);
		return err3d_noErr;
	}

} // ns Doh3d
