#pragma once

#include <array>
#include <iterator>

template <class T, size_t capacity>
void ArrayInsert(std::array<T, capacity>& array, size_t size, size_t index, const T& value) {
    if (size >= capacity) throw "insert to full array";
    if (index > size) throw "index out of range";
    for (size_t idx = size; idx != index; --idx) {
        array[idx] = array[idx - 1];
    }
    array[index] = value;
}

template <class T, size_t capacity>
void ArrayErase(std::array<T, capacity>& array, size_t size, size_t index) {
    if (size >= capacity) throw "size is more than capacity";
    for (size_t idx = index; idx < size; ++idx) {
        array[idx] = array[idx + 1];
    }
}

template <class Iterator>
Iterator BinarySearch(Iterator first, Iterator last, const typename std::iterator_traits<Iterator>::value_type& target) {
    Iterator ret = last;
    Iterator mid;
    while (first != last) {
        mid = first;
        std::advance(mid, std::distance(first, last) >> 1);
        if (*mid > target) last = mid;
        else if (*mid < target) begin = ++mid;
        else break;
    }
    if (first != last) ret = mid;
    return ret;
}

// value is usually the logical address of data on disk
template<class Key, class Value, size_t MinDegree>
class BTreeNode {
public:
    struct Element {
        Element(const Key& k = Key(), const Value& v = Value()) : key(k), value(v) {}
        Key key;
        Value value;
    };

    Value* Find(const Key& key) {
        size_t idx = 0;
        while (idx < m_degree - 1 && m_elements[idx].key < key) ++idx;
        BTreeNode* ret = nullptr;
        if (idx != m_degree - 1 && m_elements[idx].key == key) ret = &m_elements[idx].value;
        else if (!m_leaf) ret = m_children[idx]->Find(key);
        return ret;
    }

    void SplitChild(size_t index) {
        if (Full()) return;     // assume parent node is not full when spliting subnode
        BTreeNode* raw = m_children[index];
        BTreeNode* node = new BTreeNode();
        size_t center = raw->m_degree >> 1;
        node->m_degree = raw->m_degree - center;
        raw->m_degree = center;
        std::copy(raw->m_elements.begin() + center, raw->m_elements.end(), node->m_elements.begin());
        std::copy(raw->m_children.begin() + center, raw->m_children.end(), node->m_children.begin());
        ArrayInsert(m_elements, m_degree - 1, index, raw->m_elements[center]);
        ArrayInsert(m_children, m_degree, index, node);
        ++m_degree;
    }

    bool Full() { return m_degree == 2 * MinDegree; }

    void Insert(const Key& key, const Value& value) {
        if (m_leaf) {
            /*size_t idx = m_degree - 1;
            while (idx != 0 && m_keys[idx] > key) {
                m_keys[idx + 1] = m_keys[idx];
                --idx;
            }
            m_keys[idx] = key;
            ++m_degree;*/
            auto iter = BinarySearch(m_elements.begin(), m_elements.end(), [](Element & element) { element.key == key; })
        }
        else {
            size_t idx = m_degree - 1;
            while (idx != 0 && m_keys[idx] > key) {
                --idx;
            }
            if (m_children[idx]->Full()) SplitChild(idx);
            if (m_keys[idx + 1] < key) ++idx;
            m_children[idx]->Insert(key);
        }
    }

    void Delete(int index) {

    }

private:
    bool m_leaf;
    size_t m_degree;    // MinDegree <= m_degree <= 2 * MinDegree
    // key < m_keys[0] ==> key is in m_children[0]
    // key > m_keys[m_degree - 1] ==> key is in m_children m_children[m_degree]
    // m_keys[index - 1] < key < m_keys[index] ==> key is in m_children[index]
    //std::array<Key, 2 * MinDegree - 1> m_keys;
    // m_keys[index] ==> m_values[index]
    //std::array<Value, 2 * MinDegree - 1> m_values;
    std::array<Element, 2 * MinDegree - 1> m_elements;
    std::array<BTreeNode*, 2 * MinDegree> m_children;
};