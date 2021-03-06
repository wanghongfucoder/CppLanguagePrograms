#include <iostream>
#include <assert.h>
#include "LruCache.h"
using namespace std;

int main()
{
    {
        LruCache<int, int> cache(5);
        cache.put(2, 3);
        cache.put(1, 11);
        cache.put(3, 56);
        cache.put(4, 13);
        assert(11 == cache.getOrDefault(1));
        assert(56 == cache.getOrDefault(3));
        assert(3 == cache.getOrDefault(2));
        assert(!cache.hasKey(5));
        assert(111 == cache.getOrDefault(9, 111));
        int val;
        cache.get(4, val);
        assert(13 == val);
    }
    {
        LruCache<int, int> cache(3);
        cache.put(1, 1);
        cache.put(2, 2);
        cache.put(2, 1);
        cache.put(3, 3);
        cache.put(6, 4);
        assert(1 == cache.getOrDefault(2));
        assert(3 == cache.getOrDefault(3));
        assert(0 == cache.getOrDefault(1));
        assert(4 == cache.getOrDefault(6));
    }
    {
        LruCache<int, int> cache(2);
        assert(0 == cache.size());
        assert(2 == cache.capacity());
        assert(cache.empty());
        assert(!cache.full());

        cache.put(1, 1);
        assert(1 == cache.size());
        assert(!cache.empty());
        assert(!cache.full());

        cache.put(2, 2);
        assert(2 ==cache.size());
        assert(!cache.empty());
        assert(cache.full());

        cache.put(3, 3);
        assert(2 == cache.size());
        assert(!cache.empty());
        assert(cache.full());
    }
    {   // test hasKey
        LruCache<int, int> cache(2);
        cache.put(1, 1);
        assert(cache.hasKey(1));
        assert(!cache.hasKey(2));
    }
    {   // test remove
        LruCache<int, int> cache(2);
        cache.put(1, 1);
        assert(cache.remove(1));
        assert(0 == cache.size());
        assert(cache.empty());
        assert(!cache.remove(2));
    }

    system("pause");
    return 0;
}