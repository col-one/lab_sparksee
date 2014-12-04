#include <iostream>
#include "gdb/Sparksee.h"
#include "gdb/Stream.h"
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
	//ajout dun attr
	attr_t nameAttr = g->NewAttribute(modelType, L"NAME", Text, Basic);//Attr Text peut etre que basic

	//creation dun node
	oid_t modelNode = g->NewNode(modelType);

	//creation d'un text stream, false pour un append en fin de stream.
	//stream pour utiliser plus de 2048 char qui est la limite du type String
	TextStream tstrm(false);
	g->SetAttributeText(modelNode, nameAttr, &tstrm);

	//creation du text stream
	std::wstring str1(L"This is the first chunk of the text stream");
	std::wstring str2(L"This is the second chunk of the text stream");
	tstrm.Write(str1.c_str(), str1.size());
	tstrm.Write(str2.c_str(), str2.size());
	tstrm.Close();

	delete g;
	delete sess;
	delete db;
	delete sparksee;

	return 0;
}

















