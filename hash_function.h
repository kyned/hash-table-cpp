#ifndef __HASH__
#define __HASH__

#include <cstddef>

/**  @brief a hash function to be pass as a template parameter
  *         currently just calls std::hash
  *
  *  @tparam  _key    Type of key objects to be hashed.
 */
template<typename _key>
struct __hash_function {
    std::size_t operator()(_key const& key_value) const
    {
        return std::hash<_key>{}(key_value);
    }
};

#endif /* __HASH__ */
