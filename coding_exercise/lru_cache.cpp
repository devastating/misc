#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h>
using namespace std;

class LRUCache{

	struct CacheElem
	{
		int key;
		int value;
		//struct CacheElem *next;
		//struct CacheElem *prev;
		struct CacheElem *lru_next;
		struct CacheElem *lru_prev;
	};

public:
    LRUCache(int capacity) {
        m_lru_list_head = nullptr;
        m_lru_list_tail = nullptr;
        m_size = capacity;
        //m_cache_spine = 1 << (shift + 1);
        //m_cache.resize(m_cache_spine, nullptr);
        m_used = 0;
        m_elements = new CacheElem [m_size];
    }
    
    int get(int key) {
        auto old_elem = m_cache.find(key);
        if (old_elem != m_cache.end())
        {
        	//cout << "Found " << old_elem->second->key << endl;
            // TODO: adjust lru cache
            if (old_elem->second != m_lru_list_tail)
            {
            	//cout << "Move to tail " << old_elem->second->key << endl;
                remove_from_lru(old_elem->second);
                add_to_lru_tail(old_elem->second);
            }
            else
            {
            	//cout << "Tail already " << old_elem->second->key << endl;
            }
            return old_elem->second->value;
        }
        else return -1;
    }
    
    void set(int key, int value) {
        auto old_elem = m_cache.find(key);

        if (old_elem != m_cache.end())
        {
        	//cout << "set Found " << old_elem->second->key << endl;
            old_elem->second->value = value;
            // TODO: adjust lru cache
            if (old_elem->second != m_lru_list_tail)
            {
                remove_from_lru(old_elem->second);
                add_to_lru_tail(old_elem->second);
            }
            return;
        }
        
        CacheElem *new_elem;
        if (m_size == m_used)
        {
            // Remove LRU head
            auto to_remove = m_lru_list_head;
            //cout << "Erase " << to_remove->key << endl;
			m_cache.erase(to_remove->key);
            //assert(to_remove->lru_next != nullptr);
            remove_from_lru(to_remove);
            // reuse the memory
            new_elem = to_remove;
            m_used--;
        }
        else
        {
        	new_elem = &m_elements[m_used];
        }
        //cout << "Add " << key << endl;
        //auto new_elem = new CacheElem;
        new_elem->key = key;
        new_elem->value = value;
        //new_elem->next = m_cache[idx];
        //new_elem->prev = nullptr;
        m_cache[key] = new_elem;
    	add_to_lru_tail(new_elem);
        m_used++;
        //cout << "cache " << m_cache.size() << endl;
    }
private:
	inline void add_to_lru_tail(CacheElem *new_elem)
	{
		if (m_lru_list_head == nullptr)
        {
            m_lru_list_head = new_elem;
            m_lru_list_tail = new_elem;
            new_elem->lru_next = nullptr;
            new_elem->lru_prev = nullptr;
        }
        else
        {
            assert(m_lru_list_tail != nullptr);
            m_lru_list_tail->lru_next = new_elem;
            new_elem->lru_prev = m_lru_list_tail;
            new_elem->lru_next = nullptr;
            m_lru_list_tail = new_elem;
        }
        debug_list();
	}
	inline void remove_from_lru(CacheElem *elem)
	{
		if (elem == m_lru_list_head)
		{
			m_lru_list_head = elem->lru_next;

		}
		if (elem == m_lru_list_tail)
		{
			m_lru_list_tail = elem->lru_prev;

		}
		if (elem->lru_next != nullptr)
		{
			elem->lru_next->lru_prev = elem->lru_prev;
		}
		if (elem->lru_prev)
		{
			elem->lru_prev->lru_next = elem->lru_next;
		}
		debug_list();
	}
	
	void debug_list()
	{
		return;
		auto list_iter = m_lru_list_head;
		cout << "lru list: ";
		while (list_iter != nullptr)
		{
			cout << list_iter->key << " ";
			list_iter = list_iter->lru_next;
		}
		cout << endl;
	}

	unordered_map<int, CacheElem *> m_cache;
	int m_cache_spine;
	int m_size;
	int m_used;
	CacheElem *m_elements;
    CacheElem *m_lru_list_head;
    CacheElem *m_lru_list_tail;
};

void test_cache_basic()
{
	LRUCache test_cache(100);
	//test_cache.set(1, 1000);
	assert(test_cache.get(101) == -1);
	//assert(test_cache.get(1) == 1000);
	for (int i = 0; i < 100; i++)
	{
		test_cache.set(i, i + 2);
	}
	for (int i = 0; i < 100; i++)
	{
		assert(test_cache.get(i) == i + 2);
	}
}

void test_cache_one_entry()
{
	LRUCache test_cache(1);
	test_cache.set(10, 100);
	assert(test_cache.get(10) == 100);
	test_cache.set(20, 101);
	assert(test_cache.get(10) == -1);
	assert(test_cache.get(20) == 101);
}

void test_cache_leetcode()
{
	LRUCache test_cache(3);
	test_cache.set(1, 1);
	test_cache.set(2, 2);
	test_cache.set(3, 3);
	test_cache.set(4, 4);
	assert(test_cache.get(4) == 4);
	assert(test_cache.get(3) == 3);
	assert(test_cache.get(2) == 2);
	assert(test_cache.get(1) == -1);
	test_cache.set(5, 5);
	assert(test_cache.get(1) == -1);
	assert(test_cache.get(2) == 2);
	assert(test_cache.get(3) == 3);
	assert(test_cache.get(4) == -1);
	assert(test_cache.get(5) == 5);
}

int main() {
	LRUCache test_lru_cache(100);
	
	//test_cache_basic();
	//test_cache_one_entry();
	test_cache_leetcode();
	return 0;
}