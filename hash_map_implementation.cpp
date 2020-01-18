#include "hash_map.h"

#define hash_map__          hash_map<_key, _value, _hash>
#define TEMPLATE_MACRO      template<typename _key, typename _value, typename _hash>
#define compute_index_(x)   (x < table_size)?x:x-table_size;

#define DEFAULT_SIZE        64

/**@brief inserts given pair of key and value into hash table
  *
  * @param key of an element to be stored
  * @param value of an element to be stored
  *
  * @retval number of bucket in the table were pair was inserted.
  *
 */
TEMPLATE_MACRO
uint_t hash_map__::insert(const _key& key, const _value& value) {
  if (!table_load) {
    /// if table is fully occupied double it in size:
    return double_table_(key, value);
  }
  /// hash calculation:
  uint_t index_ = hash_function(key) % table_size;
  /// if bucket was empty:
  if (std::get<2>(table[index_])) {
    std::get<0>(table[index_]) = key;
    std::get<1>(table[index_]) = value;
    std::get<2>(table[index_]) = false;
    table_load--;
    return index_;
  } else {
    /// looks for an empty bucket or bucket with the same key
    /// max amount of attempts - `table_max_road` or table doubles itself in size
    for (uint_t i_ = 0; i_ <= table_max_road; i_++){
      uint_t index_i_ = compute_index_(index_ + i_);
      if ((std::get<2>(table[index_i_]))||(std::get<0>(table[index_i_]) == key)) {
        std::get<0>(table[index_i_]) = key;
        std::get<1>(table[index_i_]) = value;
        std::get<2>(table[index_i_]) = false;
        /// counts maximum missmatch - usefull when retrieving elements;
        if (table_road < i_)
            table_road = i_;
        table_load--;
        return index_i_;
      } else {
          if (table_road < i_)
            table_road = i_;
      }
    }
  }
  if (table_road == table_max_road) {
    /// if table is fully occupied double it in size:
    return double_table_(key, value);
  }
}

/**@brief marks specified bucket as empty. if nothing is found does nothing.
  *
  * @param key of an element to be removed
  *
 */
TEMPLATE_MACRO
void hash_map__::remove(const _key& key) {
  /// hash calculation:
  unsigned int index_ = hash_function(key) % table_size;
  if ((std::get<0>(table[index_]) == key) && (!std::get<2>(table[index_]))){
    std::get<2>(table[index_]) = true;
    table_load++;
  } else {
    for (unsigned int i_ = 1; i_ <= table_road; i_++) {
      unsigned int index_i_ = compute_index_(index_ + i_);
      if ((std::get<0>(table[index_i_]) == key) && (!std::get<2>(table[index_i_]))){
        std::get<1>(hash_map::table[index_i_]) = true;
        table_load++;
      }
    }
  }
}


/**@brief retrieves value stored under specified key or throws an error.
  *
  * @param key of an element to be retrieved
  *
  * @retval value stored in the bucket. if nothing is found error is thrown.
  *
 */
TEMPLATE_MACRO
_value& hash_map__::operator[](const _key& key) {
  /// hash calculation:
  unsigned int index_ = hash_function(key) % table_size;
  if ((std::get<0>(table[index_]) == key) && (!std::get<2>(table[index_])))
    return std::get<1>(table[index_]);
  else {
    for (unsigned int i_ = 1; i_ <= table_road; i_++) {
      unsigned int index_i_ = compute_index_(index_ + i_);
      if ((std::get<0>(table[index_i_]) == key) && (!std::get<2>(table[index_i_])))
        return std::get<1>(table[index_i_]);
    }
  }
  /// if nothing was found:
  throw std::out_of_range("hash_map<_key> : no such key encountered;");
}

/**@brief default constructor.
 */
TEMPLATE_MACRO
hash_map__::hash_map() {
  table_size       = DEFAULT_SIZE;
  table_load       = table_size;
  table_road       = 0;
  table_max_road   = table_size / 4;
  table        = new TUPLE_MACRO[table_size];
  /// marks all buckets as empty in the new table:
  for (uint_t i_ = 0; i_ < table_size; i_++)
    std::get<2>(table[i_]) = true;
}

/**@brief creates table of a size of passed parameter;
 */
TEMPLATE_MACRO
hash_map__::hash_map(uint_t size_) {
  table_size       = size_;
  table_load       = table_size;
  table_road       = 0;
  table_max_road   = table_size / 4;
  table        = new TUPLE_MACRO[table_size];
  /// marks all buckets as empty in the new table:
  for (int i_ = 0; i_ < table_size; i_++)
    std::get<2>(table[i_]) = true;
}

/**@brief creates a deep copy of an instance
 */
TEMPLATE_MACRO
hash_map__::hash_map(const hash_map& instance_) {
  table_size     = instance_.table_size;    
  table_load     = instance_.table_load;    
  table_road     = instance_.table_road;    
  table_max_road = instance_.table_max_road;
  table        = new TUPLE_MACRO[table_size];
  /// copies content of all buckets:
  for (int i_ = 0; i_ < table_size; i_++) {
    std::get<0>(table[i_]) = std::get<0>(instance_.table[i_]);
    std::get<1>(table[i_]) = std::get<1>(instance_.table[i_]);
    std::get<2>(table[i_]) = std::get<2>(instance_.table[i_]);
  }
}

/**@brief if during insertion attempt it was indicated that
  *        current size of the table is no longer good, this function doubles its size
  *         reinserts all previously inserted values into new table, then inserts pair
  *         of values that caused a failure.
  *
  * @param key of an object.
  * @param value of an object to be stored.
  *
  * @retval number of bucket in the table were last pair was inserted.
  *
 */
TEMPLATE_MACRO
uint_t hash_map__::double_table_(const _key& key, const _value& value) {

    /// redefines parameters of the hash_map:
    TUPLE_MACRO*    old_table_ = table;
    table_size       = table_size * 2;
    table_load       = table_size;
    table_road       = 0;
    table_max_road   = table_size / 4;

    /// creates new table
    table = new TUPLE_MACRO[table_size];

    /// marks all buckets as empty in the new table:
    for (int i_ = 0; i_ < table_size; i_++)
        std::get<2>(table[i_]) = true;

    /// inserts all previously stored values into new table:
    for (int i_ = 0; i_ < table_size / 2; i_++) {
        if (!std::get<2>(old_table_[i_])) {
           insert(std::get<0>(old_table_[i_]), std::get<1>(old_table_[i_]));
        }
    }
    delete [] old_table_;
    return insert(key, value);
}

