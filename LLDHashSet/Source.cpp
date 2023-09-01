#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define sp system("pause")

template<typename V>
struct List
{
	vector<V>arr;

	bool Find(V value)
	{
		auto it = find(arr.begin(), arr.end(), value);
		return it == arr.end() ? 0 : 1;
	}

	void Insert(V value)
	{
		if (Find(value) == true) return;
		arr.emplace_back(value);
	}

	void Erase(V value)
	{
		if (Find(value) == false) return;
		auto it = find(arr.begin(), arr.end(), value);
		arr.erase(it);
	}
};

template<typename V>
class HashSet
{
public:
	int size = 16;
	List<V>* list;
	
	HashSet(int Size)
	{
		this->size = pow(2,log2(Size) + 1);
		list = new List<V>[size];
	}


	int hash(V key)
	{
		return (int(key)) % int(size);
	}

	void insert(V value)
	{
		int Hash = hash(value);
		list[Hash].Insert(value);
	}

	bool find(V value)
	{
		int Hash = hash(value);
		return list[Hash].Find(value);
	}

	void erase(V value)
	{
		int Hash = hash(value);
		list[Hash].Erase(value);
	}
};


template<>
class HashSet <std::string>
{
public:
	int size = 16;
	List<string>* list;

	HashSet(int Size)
	{
		this->size = pow(2, log2(Size) + 1);
		list = new List<string>[size];
	}


	int hash(string key)
	{
		ll Hash = 0;
		for (int i = 0; i < key.length(); i++)
		{
			char ch = key[i];
			Hash = (Hash + (int(ch) * 107)) % size;
		}
		return Hash % size;
	}

	void insert(string value)
	{
		int Hash = hash(value);
		list[Hash].Insert(value);
	}

	bool find(string value)
	{
		int Hash = hash(value);
		return list[Hash].Find(value);
	}

	void erase(string value)
	{
		int Hash = hash(value);
		list[Hash].Erase(value);
	}
};


int main()
{
	HashSet<string>hst(10);
	hst.insert("1");
	hst.insert("12");
	hst.insert("14");

	cout << hst.find("1") << endl;
	cout << hst.find("12") << endl;
	cout << hst.find("15") << endl;

	return 0;
}