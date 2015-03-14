
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <cmath>
#include <new>

typedef struct {
	unsigned char *key;
	void *data;
}hash_data;

typedef struct {
	hash_data *tbl;
	int size;
}hash_table_t;


unsigned long djb2_hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;
	while(c=*str++)
		hash = ((hash << 5) + hash) + c;
	return hash;
}

void hash_insert(hash_table_t *tbl, hash_data *data)
{
	unsigned int index = djb2_hash(data->tbl);
	tbl->tbl[index] = data;
}

void hash_delete(hash_table_t *tbl, hash_data *data)
{

}

hash_data* hash_search(hash_table_t *tbl, hash_key *k)
{
	unsigned int index = djb2_hash(k);
	return tbl->tbl[index];
}

bool hash_initialize(hash_table_t tbl,int size)
{
	tbl->size = size;
	tbl->tbl = new (std::nothrow) hash_data[size];
	if(tbl->tbl==0)
		return false;
}


class DogRecord
{
	public:
		std::string name;
		unsigned int age;

		DogRecord(const std::string &n,int iage)
		{
			name = n;
			age = iage;
		}
};


int main(int argc,char **argv)
{

	std::vector<DogRecord> dogs;
	dogs.push_back(DogRecord("henry",2));
	dogs.push_back(DogRecord("bob",1));
	dogs.push_back(DogRecord("kate",5));
	dogs.push_back(DogRecord("pero",3));
	dogs.push_back(DogRecord("fido",5));
	dogs.push_back(DogRecord("pete",9));
	dogs.push_back(DogRecord("dexter",3));

	hash_table_t hash_table;

	hash_initialize(hash_table,200);

	for(int i=0;i<dogs.size();++i) {

		hash_insert(hash_table,dogs[i]);
	}

	return 0;
}

