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
	Database *db = NULL;

	try{
		db = sparksee->Open(L"tg.gdb", false);
	}
	catch(FileNotFoundException& e){
		std::cerr<<e.Message()<<std::endl;
		db = sparksee->Create(L"tg.gdb", L"tg");
	}
	catch(Error& e){
		std::cerr<<e.Message()<<std::endl;
	}
	//create new session and get corresponding graph
	Session *sess = db->NewSession();
	Graph *g = sess->GetGraph();


	//delete for close session
	delete g;
	delete sess;
	delete db;
	delete sparksee;

	return 0;
}

















