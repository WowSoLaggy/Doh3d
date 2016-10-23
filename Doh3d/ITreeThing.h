#pragma once

#ifndef INC_DOH3D_ITREETHING_H
#define INC_DOH3D_ITREETHING_H


namespace Doh3d
{

// T is the type of error
	template <typename T>
	class ITreeThing
	{
	public:

		virtual ~ITreeThing()
		{
			for (auto child : m_childs)
				delete child;
		}


		virtual T Draw(Sprite& pSprite, const D3DXVECTOR3& pOffset) const
		{
			T err;

			for (auto child : m_childs)
			{
				err = child->Draw(pSprite, pOffset);
				if (err != (T)0)
					return err;
			}

			return (T)0;
		}


		virtual T Load()
		{
			T err;

			for (auto child : m_childs)
			{
				err = child->Load();
				if (err != (T)0)
					return err;
			}

			return (T)0;
		}


		virtual T Unload()
		{
			T err;

			for (auto child : m_childs)
			{
				err = child->Unload();
				if (err != (T)0)
					return err;
			}

			return (T)0;
		}


		void AddChild(ITreeThing* pChild)
		{
			if (!pChild || pChild->m_parent == this)
				return;
			if (pChild->m_parent != nullptr)
				pChild->m_parent->RemoveChild(pChild);

			pChild->m_parent = this;
			m_childs.push_back(pChild);
		}

		void RemoveChild(ITreeThing* pChild)
		{
			if (!pChild || pChild->m_parent != this)
				return;
			auto& it = std::find(m_childs.begin(), m_childs.end(), pChild);
			if (it == m_childs.end())
				return;

			m_childs.erase(it);
			pChild->m_parent = nullptr;
		}

		std::vector<ITreeThing*>& GetChilds() { return m_childs; }

	protected:

		ITreeThing* m_parent;
		std::vector<ITreeThing*> m_childs;
	};

} // ns Doh3d


#endif // INC_DOH3D_ITREETHING_H
