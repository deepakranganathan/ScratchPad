#include <list>
#include <unordered_map>
#include <utility>

using namespace std;

class LRUCache
{
private:
	// Linked list to store the keys
	list<pair<int, int>> mLRUList;

	// Map to store the pointers to the keys in cache
	unordered_map<int, list<pair<int, int>>::iterator> mLRUMap;

	int mCapacity;
public:
	LRUCache(int capacity)
	{
		mCapacity = capacity;
	}

	int GetValue(int key)
	{
		auto it = mLRUMap.find(key);
		int retVal = -1;
		if (it == mLRUMap.end())
		{
			// Cache miss
			retVal = -1;
		}
		else
		{
			// Cache hit. Erase from current position and add to top of LRU
			mLRUList.splice(mLRUList.begin(), mLRUList, it->second);
			retVal = it->second->second;
		}

		return retVal;
	}

	void PutValue(int key, int value)
	{
		auto it = mLRUMap.find(key);
		if (it == mLRUMap.end())
		{
			// Cache miss
			if (mLRUList.size() == mCapacity)
			{

				// Cache is full. We need to evict the LRU
				mLRUMap.erase(mLRUList.rbegin()->first);
				mLRUList.pop_back();
			}
		}
		else
		{
			// Cache hit. Erase from current position. We will add to top of LRU later
			mLRUList.erase(it->second);
		}

		// Update the LRU reference for the new entry
		mLRUList.push_front(make_pair(key, value));
		mLRUMap[key] = mLRUList.begin();
	}
};

void TestLRUCache()
{

	LRUCache cache(2);

	cache.PutValue(1, 1);
	cache.PutValue(2, 2);
	printf("%d\n", cache.GetValue(1)); // returns 1  
	cache.PutValue(3, 3);    // evicts 2
	printf("%d\n", cache.GetValue(2)); // returns -1 for not found
	cache.PutValue(4, 4);    // evicts 1  
	printf("%d\n", cache.GetValue(1)); // returns -1 for not found
	printf("%d\n", cache.GetValue(3)); // returns 3
	printf("%d\n", cache.GetValue(4)); // returns 4
}