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

	//creation dun nouveau type
	type_t modelType = g->NewNodeType(L"MODEL");


	//creation de deux nouveaux node
	oid_t modelNode = g->NewNode(modelType);
	oid_t modelNodeB = g->NewNode(modelType);


	//creation d'un nouveau type de link/edge
	/*Parameters:
    	name 	[in] Unique name for the new edge type.
    	directed 	[in] If TRUE, this creates a directed edge type, otherwise this creates a undirected edge type.
    	neighbors 	[in] If TRUE, this indexes neighbor nodes, otherwise not.

		Returns:
    	Unique Sparksee type identifier.
    */
	type_t referenceLinkType = g->NewEdgeType(L"REFERENCE", true, true);

	//creation dun nouveau link/edge
	oid_t referenceLink = g->NewEdge(referenceLinkType, modelNode, modelNodeB);

	//print les integer oid_t
	std::cerr<<referenceLink<<std::endl<<modelNodeB<<std::endl<<modelNode<<std::endl;

	//delete for close session
	delete g;
	delete sess;
	delete db;
	delete sparksee;

	return 0;
}

















