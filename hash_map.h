#ifndef __HASH_MAP__
#define __HASH_MAP__

#include <tuple>
#include <cstddef>
#include "hash_function.h"

/// bool parameter indicates that certain bucket is occupied:
#define TUPLE_MACRO             std::tuple<_key, _value, bool>
#define uint_t                  unsigned int

/**  @brief hash table with open addressing;
  * 
  *  @tparam  _key    Type of key objects.
  *  @tparam  _value  Type of mapped objects.
  *  @tparam  _hash   Hashing function object type, default is implemented in hash_function.h.
 */
template<typename _key, typename _value, typename _hash = __hash_function<_key>>
class hash_map {
  /* private members:             */
  TUPLE_MACRO*    table;           // pointer to the hash_table vector;
  uint_t          table_size;      // size of currently allocated memory in units;
  uint_t          table_load;      // amount of currently stored elements in the table; 
  uint_t          table_road;      // counter of max collisions in a row that occured;
  uint_t          table_max_road;  // max allowed amount of collisions in a row;

  _hash     hash_function;
  uint_t    double_table_(const _key& key, const _value& value); // doubles current table in size;

  public:
    /* public functions:          */
    uint_t      insert(const _key& key, const _value& value);
    void        remove(const _key& key);
    _value& operator[](const _key& key);  // search algorithm. also allows to change previously stored value.

    hash_map();                           // default constructor;
    hash_map(uint_t);                     // takes size of the table to create as a parameter;
    hash_map(const hash_map&);            // copy constructor;
    ~hash_map() { delete [] table; }
};

#endif /* __HASH_MAP__ */
