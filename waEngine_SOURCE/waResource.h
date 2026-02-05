#pragma once
#include "waEntity.h"

namespace wa
{
	class Resource : public Entity
	{
	public:
		Resource(enums::eResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0; // 순수가상함수 실제 메모리 할당이 불가능해지는 문법 // HRESULT는 그냥 bool 임

		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		const enums::eResourceType mType;
		std::wstring mPath;

	};
}
