#include <iostream>
#include "gdb/Sparksee.h"
#include "gdb/Database.h"
#include "gdb/Session.h"
#include "gdb/Graph.h"
#include "gdb/Objects.h"
#include "gdb/ObjectsIterator.h"

using namespace sparksee::gdb;

int main(int argc, char *argv[])
{
	//config and create db
	SparkseeConfig cfg;
	Sparksee *sparksee = new Sparksee(cfg);
	Database *db = sparksee->Create(L"tg.gdb", L"tg");
	//create new session and get corresponding graph
	Session *sess = db->NewSession();
	Graph *g = sess->GetGraph();

	//creation dun nouveau type
	type_t modelType = g->NewNodeType(L"MODEL");


	//creation de deux nouveaux node
	oid_t modelNode = g->NewNode(modelType);
	oid_t modelNodeB = g->NewNode(modelType);

	//verifie l'existance de lattr
	//et ajout de lattr au nodeType si besoin
	attr_t nameAttrId = g->FindAttribute(modelType, L"Name");
	if (Attribute::InvalidAttribute == nameAttrId)
	{
	    nameAttrId = g->NewAttribute(modelType, L"Name", String, Indexed);
	}

	//value utilisation de la class value pour set les attr
	Value v;
	g->SetAttribute(modelNode, nameAttrId, v.SetString(L"toto los patos"));
	g->SetAttribute(modelNodeB, nameAttrId, v.SetString(L"tata los potas"));

	AttributeList *aList = g->GetAttributes(modelNode);
	AttributeListIterator *aListIt = aList->Iterator();
	while(aListIt->HasNext()){
		attr_t attrT = aListIt->Next();
		Attribute *attr = g->GetAttribute(attrT);
		std::wcout<<attr->GetName()<<std::endl;
	}


	delete g;
	delete sess;
	delete db;
	delete sparksee;

	return 0;
}

















