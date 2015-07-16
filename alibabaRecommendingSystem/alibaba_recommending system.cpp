#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <vector>

using namespace std;
const string s[] = { "ok", "浏览", "收藏", "加购物车", "购买" };

typedef struct item
{
	int behavior_type;		//用户对商品的行为类型 包括浏览、收藏、加购物车、购买，对应取值分别是1、2、3、4。
	int count;
	string time;
	struct item *next;
	item(int behavior_type, string time)
	{
		this->behavior_type = behavior_type;
		this->count = 0;
		this->time = time;
		next = NULL;
	}
}Item_behavior;

map<int, Item_behavior*> *items;
map<int, Item_behavior*>::iterator items_i;

map<int, map<int, Item_behavior*>* >::iterator map_cate_item_i;

class UserBehavior
{
public:
	int user_id;			//用户标识,抽样&字段脱敏
	string user_geohash;	//用户位置的空间标识，可以为空 由经纬度通过保密的算法生成
	
	//统计
	map<int, map<int, Item_behavior*>* > map_cate_item;  // cate_id => (item_id => behavior)
	
	UserBehavior(int user_id, string user_geohash){
		this->user_id = user_id;
		this->user_geohash = user_geohash;

	}
	void dump(){
		cout << "Behaviors\n\tuser_id:" << this->user_id << " user_geohash:" << this->user_geohash << endl;


		for (map_cate_item_i = this->map_cate_item.begin(); map_cate_item_i != map_cate_item.end(); (map_cate_item_i)++)
		{
			items = map_cate_item_i->second;
			cout << "    cate_id:" << map_cate_item_i->first << " itemsnum:"<<items->size()<<endl;
			for (items_i = items->begin(); items_i != items->end(); (items_i)++)
			{
				Item_behavior *temp = items_i->second;
				cout << "       item_id:" << items_i->first<<endl;
				while (temp != NULL)
				{
					// cout<<"\t\t\titem_id:"<<temp->item_id;		
					cout << "         beh_type:" << s[temp->behavior_type];
					// cout << " item_category:" << temp->item_category;
					cout << " time:" << temp->time << endl;
					temp = temp->next;
				}
			}
			
		}
		cout << "\n---END---\n" << endl;
	}
	void free(){
		for (map_cate_item_i = this->map_cate_item.begin(); map_cate_item_i != map_cate_item.end(); (map_cate_item_i)++)
		{
			items = map_cate_item_i->second;
			for (items_i = items->begin(); items_i != items->end(); (items_i)++)
			{
				Item_behavior *temp = items_i->second;
				Item_behavior *temp2;
				cout << "    item_id:" << items_i->first << endl;
				while (temp != NULL)
				{
					
					temp2 = temp->next;
					
					
				}
			}

		}
	}
	
};


class Item{
public:
	int item_id, item_category;
	vector<string> item_geohash;
	Item(int item_id, string item_geohash, int item_category){

		this->item_id = item_id;
		this->item_geohash.push_back(item_geohash);
		this->item_category = item_category;
	}
};
int insert_cate(UserBehavior *UB, int item_category, int item_id, int behavior_type, string time){
	Item_behavior *new_item_behavior = new Item_behavior(behavior_type, time);
	if ((map_cate_item_i = UB->map_cate_item.find(item_category)) != UB->map_cate_item.end())
		//若该cate_id 存在
	{
		map<int, Item_behavior*> *i = map_cate_item_i->second;
		map<int, Item_behavior*>::iterator i_i;
		if ((i_i = i->find(item_id)) != i->end()) //在map<int, Item_behavior*>找到item_id后
		{
			Item_behavior *item_behavior = i_i->second;
			Item_behavior *item_behavior_temp;
			if (item_behavior->time > time)
			{
				new_item_behavior->next = item_behavior;
				(*i)[item_id] = new_item_behavior;
				//i->insert(map<int, Item_behavior*>::value_type(item_id, new_item_behavior));
			}
			// Item_behavior *item_behavior_temp = tempBehavior->items_i->second;
			else
			{
				
				while (item_behavior->next != NULL && time > item_behavior->time)
				{
					item_behavior = item_behavior->next;
				}
				item_behavior_temp = item_behavior->next;
				item_behavior->next = new_item_behavior;
				new_item_behavior->next = item_behavior_temp;
			}
		}
		else
		{
			i->insert(map<int, Item_behavior*>::value_type(item_id, new_item_behavior));
		}

		return 1;

	}
	else //若cate_id 不存在
	{
		map<int, Item_behavior*> *temp_map = new map<int, Item_behavior*>;
		temp_map->insert(map<int, Item_behavior*>::value_type(item_id, new_item_behavior));

		UB->map_cate_item.insert(map<int, map<int, Item_behavior*>* >::value_type(item_category, temp_map));

		return 1;
	}

}
map<int, Item*> map_item;
map<int, Item*>::iterator f;

map<int, UserBehavior*> map_behavior;
map<int, UserBehavior*>::iterator behavior_iterator;


bool get_file_items(char *file_name){
	fstream file_item(file_name, ios::in);
	if (!file_item.is_open())
	{
		return false;
	}
	string templine;
	getline(file_item, templine);//丢弃首行	

	int item_id, item_category;
	string item_geohash;
	for (int j = 0, k = 0, start = 0; getline(file_item, templine); j = 0, k = 0, start = 0)
	{

		while (templine[j] != '\0')
		{
			if (templine[j] == ',')
			{

				if (k == 0)
				{
					item_id = atoi(templine.substr(start, j - start).c_str());
				}
				if (k == 1)
				{
					item_geohash = templine.substr(start, j - start);
				}
				k++;
				start = j + 1;
			}
			j++;
		}
		item_category = atoi(templine.substr(start, j - start).c_str());
		// cout<<item_id<<" "<<item_geohash<<" "<<item_category<<" "<<endl;
		if ((f = map_item.find(item_id)) != map_item.end())
		{
			f->second->item_geohash.push_back(item_geohash);
		}
		else
		{
			Item *item = new Item(item_id, item_geohash, item_category);
			map_item[item_id] = item;
		}

		// cout<<endl;
	}
	file_item.close();
	return true;
}


bool get_file_behaviors(char *file_name){
	fstream file_item(file_name, ios::in);
	if (!file_item.is_open())
	{
		return false;
	}
	string templine;
	getline(file_item, templine);//丢弃首行	

	int user_id, item_id, behavior_type, item_category;
	string user_geohash, time;

	UserBehavior *tempBehavior = NULL;
	for (int i = 0, j = 0, k = 0, start = 0;i<5000000; i++, j = 0, k = 0, start = 0)
	{
		getline(file_item, templine);
		// cout<<templine<<endl;
		while (templine[j] != '\0')
		{
			if (templine[j] == ',')
			{
				if (k == 0)
				{
					user_id = atoi(templine.substr(start, j - start).c_str());
					
				}
				if (k == 1)
				{
					item_id = atoi(templine.substr(start, j - start).c_str());
				}
				if (k == 2)
				{
					behavior_type = atoi(templine.substr(start, j - start).c_str());
				}
				if (k == 3)
				{
					user_geohash = templine.substr(start, j - start);
				}
				if (k == 4)
				{
					item_category = atoi(templine.substr(start, j - start).c_str());
				}
				k++;
				start = j + 1;
			}
			j++;
		}
		time = templine.substr(start, j - start);
		//if (user_id != 99512554) continue;
		if ((behavior_iterator = map_behavior.find(user_id)) != map_behavior.end())
		{
			tempBehavior = behavior_iterator->second;
			insert_cate(tempBehavior,item_category, item_id, behavior_type, time);

		}
		else
		{
			UserBehavior *new_UserBehavior = new UserBehavior(user_id, user_geohash);
			insert_cate(new_UserBehavior,item_category, item_id, behavior_type, time);
			map_behavior[user_id] = new_UserBehavior;
		}
	}
	
	file_item.close();
	return true;
}
int main(int argc, char const *argv[])
{
	// cout<<"hello"<<endl;

	int item_id, user_id;
	char file1[] = "tianchi_mobile_recommend_train_item.csv";
	char file2[] = "tianchi_mobile_recommend_train_user.csv";
	//char file2[] = "1.txt";

	
	/*if (get_file_items(file1))
	{
		cout << "open tianchi_mobile_recommend_train_item.csv success! " << endl;
	}
	else
	{
		cout << "open tianchi_mobile_recommend_train_item.csv fail! " << endl;
	}*/

	if (get_file_behaviors(file2))
	{
		cout << "open tianchi_mobile_recommend_train_item.csv success! " << endl;
		cout << sizeof(map_behavior) << endl;
	}
	else
	{
		cout << "open tianchi_mobile_recommend_train_item.csv fail! " << endl;
	}


	while (cin >> user_id)
	{

		if ((behavior_iterator = map_behavior.find(user_id)) != map_behavior.end())
		{
			cout << "user_id:" << user_id << endl;

			behavior_iterator->second->dump();
			/*if(behavior_iterator->second->items.size() == 0)
			{
			cout<<" "<<behavior_iterator->second->items[0]<<" "<<behavior_iterator->second->item_category<<endl;
			}
			else
			{
			for (int i = 0; i < behavior_iterator->second->item_geohash.size(); ++i)
			{
			cout<<behavior_iterator->second->item_id<<" "<<behavior_iterator->second->item_geohash[i]<<" "<<behavior_iterator->second->item_category<<endl;
			}

			}*/

		}
		else
		{
			cout << "Not find" << endl;
		}
	}

	system("pause");
	return 0;
}