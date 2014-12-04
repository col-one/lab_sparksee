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


	//find type "MODEL"
	type_t modelTypeB = g->FindType(L"MODEL");
	Type *tType = g->GetType(modelTypeB);
	std::wcout<<L"Type type "<< tType->GetName() << std::endl;

	delete tType;

	//check validite/existance du type_t par secu, si false recreer un type
	TypeList *tList = g->FindNodeTypes();
	TypeListIterator *tListIt = tList->Iterator();
	while(tListIt->HasNext()){
		type_t type = tListIt->Next();
		Type *tData = g->GetType(type);
		std::wcout<<L"Type "<< tData->GetName() << std::endl;
		delete tData;
	}
	delete tListIt;
	delete tList;
	//delete for close session
	delete g;
	delete sess;
	delete db;
	delete sparksee;

	return 0;
}

















