
#include "RigolCom.h"

extern "C"
{
	RigolCom* RigolCom_new() { return new RigolCom(); }

	void RigolCom_OnSendCommand(RigolCom* rigolCom, CString command, CString& strInstr) { return rigolCom->OnSendCommand(command, strInstr); }

}


// g++ -c -DGUI -fPIC -std=c++11 -I. interface.cpp RigolCom.cpp