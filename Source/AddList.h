#pragma once

#include <memory>
#include <list>

class Obj;

//individual object's pointer
using Objshared = std::shared_ptr<Obj>;
// individual object's pointer's list
using Shared_ObjList = std::list<Objshared>;
// first addrress of Objshared
using Shared_ObjListptr = std::shared_ptr<Shared_ObjList>;

using WeakList = std::weak_ptr<Shared_ObjList>;

using List_Obj_itr = Shared_ObjList::iterator;

//objektをｲﾝｽﾀﾝｽしたときにlistに加えていく
struct AddList
{
	List_Obj_itr operator()(WeakList objlist, Objshared objPtr)
	{
		//	所有権を持っていた引数のobjPtrからobjListに追加された新たなobjPtrに所有権が譲渡される。
		//	shared_ptr でも所有権の譲渡、放棄は可能（書いても書かなくてもよい）
		//	所有権の譲渡
		objlist.lock()->push_back(objPtr);

		//	終端
		List_Obj_itr itr = objlist.lock()->end();
		//	終端から前に向かってﾏｲﾅｽしてあげる
		itr--;
		//	ここからautoの型推論をやっている。
		return itr;
	}
};

