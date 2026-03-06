#include "waCollisionManager.h"
#include "waScene.h"
#include "waSceneManager.h"
#include "waGameObject.h"
#include "waCollider.h"
#include "waTransform.h"

namespace wa 
{
	std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};
	std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{

	}

	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();

		for (UINT row = 0; row < (UINT)eLayerType::Max; row++)
		{
			for (UINT col = 0; col < (UINT)eLayerType::Max; col++)
			{
				if (mCollisionLayerMatrix[row][col] == true)
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}

	}

	void CollisionManager::LateUpdate()
	{

	}

	void CollisionManager::Render(HDC hdc)
	{

	}
	void CollisionManager::Clear()
	{
		mCollisionMap.clear();
		mCollisionLayerMatrix->reset();
	}

	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = 0;
		int col = 0;

		if (left <= right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}

		mCollisionLayerMatrix[row][col] = enable;
	}

	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = SceneManager::GetGameObjects(left);
		const std::vector<GameObject*>& rights = SceneManager::GetGameObjects(right);

		for (GameObject* left : lefts)
		{
			if (left->IsActive() == false)
				continue;
			
			Collider* leftCol = left->GetComponent<Collider>();
			if (left->GetComponent<Collider>() == nullptr)
				continue;

			for (GameObject* right : rights)
			{
				if (right->IsActive() == false)
					continue;
	
				Collider* rightCol = right->GetComponent<Collider>();
				if (right->GetComponent<Collider>() == nullptr)
					continue;
				if (left == right)
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}
	}
	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		// 두 충돌체 번호를 가져온 ID를 확인해서 CollisionID 를 세팅
		CollisionID id = {};
		id.left = left->GetID();
		id.right = right->GetID();

		// 해당 id로 충돌체 정보를 검색해준다.
		// 만약 충돌체 정보가 없다면 충돌정보를 생성해준다.
		auto iter = mCollisionMap.find(id.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		// 충돌체크를 해준다.
		if (Intersect(left, right))
		{
			// 최초 충돌
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else // 이미 충돌 중
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			if (iter->second = true) // 충돌 벗어나는 순간
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);

				iter->second = false;
			}

		}

	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
		Vector2 rightPos = rightTr->GetPosition() + right->GetOffset();

		Vector2 leftSize = left->GetSize() * 100.f;
		Vector2 rightSize = right->GetSize() * 100.f;

		// AABB 충돌
		enums::eColliderType leftType = left->GetColliderType();
		enums::eColliderType rightType = right->GetColliderType();

		if (leftType == enums::eColliderType::Rect2D
			&& rightType == enums::eColliderType::Rect2D)
		{
			if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x)
				&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y))
			{
				return true;
			}
		}

		// circle - circle 충돌
		if (leftType == enums::eColliderType::Circle2D
			&& rightType == enums::eColliderType::Circle2D)
		{
			Vector2 leftCirclePos = leftPos + (leftSize / 2.0f);
			Vector2 rightCirclePos = rightPos + (rightSize / 2.0f);

			float distance = (leftCirclePos - rightCirclePos).length();
			if (distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f))
			{
				return true;
			}
		}

		// rect - circle 충돌
		if (leftType == enums::eColliderType::Rect2D && rightType == enums::eColliderType::Circle2D
			|| leftType == enums::eColliderType::Circle2D && rightType == enums::eColliderType::Rect2D)
		{
			bool isLeftRect = (leftType == enums::eColliderType::Rect2D);

			// rect
			Vector2 rPos = isLeftRect ? leftPos : rightPos;   
			Vector2 rSize = isLeftRect ? leftSize : rightSize;
			
			// circle
			Vector2 cPos = isLeftRect ? rightPos : leftPos;   
			float cRadius = (isLeftRect ? rightSize.x : leftSize.x) / 2.0f;

			// 사각형의 각 변의 위치 계산
			float rLeft = rPos.x - (rSize.x / 2.0f);
			float rRight = rPos.x + (rSize.x / 2.0f);
			float rTop = rPos.y - (rSize.y / 2.0f);
			float rBottom = rPos.y + (rSize.y / 2.0f);

			// 원의 중심에서 가장 가까운 점 찾기 (clamp)
			float closestX = max(rLeft, min(cPos.x, rRight));
			float closestY = max(rTop, min(cPos.y, rBottom));

			Vector2 diff = cPos - Vector2(closestX, closestY);
			float distance = diff.length();

			if (distance <= cRadius)
			{
				return true;
			}
		}

		return false;
	}
}