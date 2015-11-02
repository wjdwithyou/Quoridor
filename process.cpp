#include "process.h"
//#include <cstdlib>
#include "menuProcess.h"

#include "common.h"	/////
#include "gameProcess.h"	/////

Process::Process(){}
Process::~Process(){}

void Process::InitList(Process*** p_list, Process** cur) const{
	*p_list = new Process*[NUM_STAT];

	(*p_list)[p_menu] = new MenuProcess();
	(*p_list)[p_game] = new GameProcess();

	*cur = (*p_list)[p_menu];

	g_process = p_menu;
	g_process_cur = cur;
	g_process_list0 = *p_list;

	return;
}

void Process::Init(int){
	// virtual
	return;
}

void Process::Loop() const{
	// virtual
	return;
}