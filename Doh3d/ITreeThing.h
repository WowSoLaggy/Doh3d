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
			for (auto child : d_childs)
				delete child;
		}


		// TODO: Move such funcs to the separate interface
		virtual T draw(Sprite& pSprite, const D3DXVECTOR3& pOffset) const
		{
			T err;

			for (auto child : d_childs)
			{
				err = child->draw(pSprite, pOffset);
				if (err != (T)0)
					return err;
			}

			return (T)0;
		}


		virtual T load()
		{
			T err;

			for (auto child : d_childs)
			{
				err = child->load();
				if (err != (T)0)
					return err;
			}

			return (T)0;
		}


		virtual T unload()
		{
			T err;

			for (auto child : d_childs)
			{
				err = child->unload();
				if (err != (T)0)
					return err;
			}

			return (T)0;
		}


		virtual T update(float pDeltaTime)
		{
			T err;

			for (auto child : d_childs)
			{
				err = child->update(pDeltaTime);
				if (err != (T)0)
					return err;
			}

			return (T)0;
		}


		ITreeThing* addChild(ITreeThing* pChild)
		{
			if (!pChild || pChild->d_parent == this)
				return nullptr;
			if (pChild->d_parent != nullptr)
				pChild->d_parent->removeChild(pChild);

			pChild->d_parent = this;
			d_childs.push_back(pChild);

			return pChild;
		}

		void removeChild(ITreeThing* pChild)
		{
			if (!pChild || pChild->d_parent != this)
				return;
			auto& it = std::find(d_childs.begin(), d_childs.end(), pChild);
			if (it == d_childs.end())
				return;

			d_childs.erase(it);
			pChild->d_parent = nullptr;
		}

		ITreeThing* parent() { return d_parent; }
		const ITreeThing* parent() const { return d_parent; }

		std::vector<ITreeThing*>& getChilds() { return d_childs; }
		const std::vector<ITreeThing*>& getChilds() const { return d_childs; }

	protected:

		ITreeThing* d_parent;
		std::vector<ITreeThing*> d_childs;
	};

} // ns Doh3d


#endif // INC_DOH3D_ITREETHING_H
