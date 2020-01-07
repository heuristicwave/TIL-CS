#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <GMem> // #include "gmem.h"

using namespace std;

void foo() {
	malloc(4);
	calloc(256, 4);
	new int;
	new int[256];
}

void vector_test() {
    vector<uint64_t> v; // 8byte alignment

    v.reserve(5); // 40byte v.push_back(6) : 80byte
    v.push_back(1); // 8
    v.push_back(2); // 16
    v.push_back(3); // 32
    v.push_back(4);
    v.push_back(5); // 64
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    v.push_back(9); // 128
    v.push_back(10);

    for (vector<uint64_t>::iterator it = v.begin(); it != v.end(); it++) // it++ 8byte
		cout << *it << endl;
}

void list_test() {
	list<uint64_t> l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.push_back(6);
	l.push_back(7);
	l.push_back(8);
	l.push_back(9);
	l.push_back(10);

	for (list<uint64_t>::iterator it = l.begin(); it != l.end(); it++)
		cout << *it << endl;
}

void set_test() {
	set<uint64_t> s;
    // binary search 40byte => big O log n
    // 8+8+8+8+8(need 5 pointers) : previous + next + left + right +
    s.insert(1);    // 40 byte
	s.insert(2);
	s.insert(3);
	s.insert(4);
	s.insert(5);
	s.insert(6);
	s.insert(7);
	s.insert(8);
	s.insert(9);
	s.insert(10);

	for (set<uint64_t>::iterator it = s.begin(); it != s.end(); it++)
		cout << *it << endl;
}

void map_test() {
	map<uint64_t, uint64_t> m;
    // key & value, set only key => 40 + 8 : 48byte allocate
	m[1] = 100;
	m[2] = 200;
	m[3] = 300;
	m[4] = 400;
	m[5] = 500;
	m[6] = 600;
	m[7] = 700;
	m[8] = 800;
	m[9] = 900;
	m[10] = 1000;

	for (map<uint64_t, uint64_t>::iterator it = m.begin(); it != m.end(); it++)
		cout << it->second << endl;
}

void unordered_set_test() {
	unordered_set<uint64_t> us;
    // hashmap in Java
    // get info bucket index size : .bucket_count (increase prime num)

    us.insert(1); cout << us.bucket_count() << endl;
    us.insert(2); cout << us.bucket_count() << endl;
    us.insert(3); cout << us.bucket_count() << endl;
    us.insert(4); cout << us.bucket_count() << endl;
    us.insert(5); cout << us.bucket_count() << endl;
    us.insert(6); cout << us.bucket_count() << endl;
    us.insert(7); cout << us.bucket_count() << endl;
    us.insert(8); cout << us.bucket_count() << endl;
    us.insert(9); cout << us.bucket_count() << endl;
    us.insert(10); cout << us.bucket_count() << endl;

	for (unordered_set<uint64_t>::iterator it = us.begin(); it != us.end(); it++)
		cout << *it << endl;
}

void unordered_map_test() {
	unordered_map<uint64_t, uint64_t> um;

    um[1] = 100;    // alocate 24 byte
	um[2] = 200;
	um[3] = 300;
	um[4] = 400;
	um[5] = 500;
	um[6] = 600;
	um[7] = 700;
	um[8] = 800;
	um[9] = 900;
	um[10] = 1000;

	for (unordered_map<uint64_t, uint64_t>::iterator it = um.begin(); it != um.end(); it++)
		cout << it->second << endl;
}

int main()
{
//    foo();
    gmem_set_verbose(true);
//    void *temp = malloc(500);
//    free(temp);
  cout << "*** vector_test ***" << endl; vector_test();
//  cout << "*** list_test ***" << endl; list_test();
//  cout << "*** set_test ***" << endl; set_test();
//  cout << "*** map_test ***" << endl; map_test();
//    cout << "*** unordered_set_test ***" << endl; unordered_set_test();
//    cout << "*** unordered_map_test ***" << endl; unordered_map_test();
}
