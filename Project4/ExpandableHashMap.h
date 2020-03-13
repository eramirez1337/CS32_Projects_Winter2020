// ExpandableHashMap.h

// Skeleton for the ExpandableHashMap class template.  You must implement the first six
// member functions.

#ifndef EXPANDABLEHASHMAP_H
#define EXPANDABLEHASHMAP_H

template<typename KeyType, typename ValueType>
class ExpandableHashMap
{
public:
	ExpandableHashMap(double maximumLoadFactor = 0.5);
	~ExpandableHashMap();
	void reset();
	int size() const;
	void associate(const KeyType& key, const ValueType& value);

	  // for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const;

	  // for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const ExpandableHashMap*>(this)->find(key));
	}

	  // C++11 syntax for preventing copying and assignment
	ExpandableHashMap(const ExpandableHashMap&) = delete;
	ExpandableHashMap& operator=(const ExpandableHashMap&) = delete;

private:
    std::vector<std::list<std::pair<KeyType, ValueType>>> m_map; //Vector of lists of pairs of type bucket, as suggested by a TA
    size_t m_pairs;
    double m_maxLoadFactor;
    unsigned getBucketNumber(const KeyType &key) const
    {
        unsigned int hasher(const KeyType &k);
        unsigned int h = hasher(key);
        return (h % m_map.size());
    }
};

//For these next few functions, a TA guided me through the process of development; if anything seems out of the scope of the class, it wasn't me, it was the TA who allowed me to do this :)
template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::ExpandableHashMap(double maximumLoadFactor): m_map(8), m_pairs(0), m_maxLoadFactor(maximumLoadFactor)
{
}

template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::~ExpandableHashMap()
{
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::reset()
{
    m_map.clear();
    m_pairs = 0;
    m_map.resize(8);
}

template<typename KeyType, typename ValueType>
int ExpandableHashMap<KeyType, ValueType>::size() const
{
    return m_pairs;
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    if (find(key) != nullptr)
    {
        ValueType* valueInBucket = find(key);
        *valueInBucket = value;
        return;
    }
    if (static_cast<double>(m_pairs) / m_map.size() > m_maxLoadFactor)
    {
        std::vector<std::list<std::pair<KeyType, ValueType>>> temp(m_map.size() * 2);
        std::swap(m_map, temp);
        for (std::list<std::pair<KeyType, ValueType>>& bucket: temp )
        {
            for (auto& [k, v]: bucket)
            {
                m_map[getBucketNumber(k)].emplace_back(k, v);
            }
        }
    }
    m_map[getBucketNumber(key)].emplace_back(key, value);
    m_pairs++;
}

template<typename KeyType, typename ValueType>
const ValueType* ExpandableHashMap<KeyType, ValueType>::find(const KeyType& key) const
{
    unsigned int h = getBucketNumber(key);
    //std::cerr << h << std::endl;
    if (m_map[h].empty())
        return nullptr;
    for (auto it = m_map[h].begin(); it != m_map[h].end(); ++it)
    {
        if ((*it).first == key)
            return &((*it).second);
    }
    return nullptr;
}

#endif /* EXPANDABLEHASHMAP_H */
