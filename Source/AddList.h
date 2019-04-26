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

//objekt��ݽ�ݽ�����Ƃ���list�ɉ����Ă���
struct AddList
{
	List_Obj_itr operator()(WeakList objlist, Objshared objPtr)
	{
		//	���L���������Ă���������objPtr����objList�ɒǉ����ꂽ�V����objPtr�ɏ��L�������n�����B
		//	shared_ptr �ł����L���̏��n�A�����͉\�i�����Ă������Ȃ��Ă��悢�j
		//	���L���̏��n
		objlist.lock()->push_back(objPtr);

		//	�I�[
		List_Obj_itr itr = objlist.lock()->end();
		//	�I�[����O�Ɍ�������ϲŽ���Ă�����
		itr--;
		//	��������auto�̌^���_������Ă���B
		return itr;
	}
};

