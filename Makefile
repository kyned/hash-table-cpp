CC = g++

insertion_test: test/insertion_test.cpp hash_map.h hash_map_implementation.cpp
	$(CC) $< -o $@
	./$@ --verbose
