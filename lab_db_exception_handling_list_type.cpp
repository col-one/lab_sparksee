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
	//cfg.SetRecoveryEnabled(true);

	Sparksee *sparksee = new Sparksee(cfg);
	Database *db = sparksee->Create(L"tg.gdb", L"tg");

	//create new session and get corresponding graph
	Session *sess = db->NewSession();
	Graph *g = sess->GetGraph();

	type_t movieType = g->NewNodeType(L"Trolo");
	attr_t movieIdType = g->NewAttribute(movieType, L"ID", Long, Unique);
	attr_t movieTitleType = g->NewAttribute(movieType, L"TITLE", String, Indexed);
	attr_t movieYearType = g->NewAttribute(movieType, L"YEAR", Integer, Indexed);

	//exception handling already existe
	try{
		//creation des types de nodes et leurs attr
		type_t movieType = g->NewNodeType(L"Trolo");
		attr_t movieIdType = g->NewAttribute(movieType, L"ID", Long, Unique);
		attr_t movieTitleType = g->NewAttribute(movieType, L"TITLE", String, Indexed);
		attr_t movieYearType = g->NewAttribute(movieType, L"YEAR", Integer, Indexed);
	}
	catch(Error& e){
		std::cerr<<e.Message()<<std::endl;
	}
	catch(...){
		std::cerr<<"Unknow error";
	}

	//List type and his objects
	TypeList *tList = g->FindTypes();
	TypeListIterator *tlistIt = tList->Iterator();
	while(tlistIt->HasNext()){
		type_t type = tlistIt->Next();
		Type *tdata = g->GetType(type);
		std::wcout << L"Type " << tdata->GetName() << L" with " << tdata->GetNumObjects() << L" objects" << std::endl;
		delete tdata;
	}

	//delete for close session
	delete tList;
	delete tlistIt;
	delete g;
	delete sess;
	delete db;
	delete sparksee;

	return 0;
}

















