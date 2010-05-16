#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <string>
#include "execcmd.h"
#include "logbuffer.h"
#include "../scenes/entities/worldb.h"
#include "settings.h"
#include "critterselection.h"
#include "../scenes/gui/maincanvas.h"

using namespace std;

class Commands
{
	struct cmd
	{
		cmdtype commandtype;
		cmdargtype argtype;
		void (WorldB::*worldMember)();
		void (Commands::*commandsMember)();
		void (Commands::*commandsMember_uint)(const unsigned int&);
		void (Maincanvas::*canvasMember)();
		void (Maincanvas::*canvasMember_string)(const string&);
		void (Settings::*settingsMember)();
		void (Settings::*settingsMember_string)(const string&);
		void (Critterselection::*critterselectionMember)();
		void (Critterselection::*critterselectionMember_uint)(const unsigned int&);
		void (*member)(int);
	};


	public:
		static Commands* Instance();
		~Commands();

		WorldB* world;
		Maincanvas* canvas;
		void execCmd(const cmdsettings& cmds);

		void quit();
	protected:
		Commands();
	private:
		static Commands* _instance;
		Settings*		settings;
		Critterselection*	critterselection;

		void execCmd(const string& name);
		void execCmd(const string& name, const string& str);
		void execCmd(const string& name, const unsigned int& ui);

		void registerCmd(string name, void (Commands::*pt2Func)());
		void registerCmd(string name, void (Commands::*pt2Func)(const unsigned int&));
		void registerCmd(string name, void (WorldB::*pt2Func)());
		void registerCmd(string name, void (Maincanvas::*pt2Func)());
		void registerCmd(string name, void (Maincanvas::*pt2Func)(const string&));
		void registerCmd(string name, void (Settings::*pt2Func)());
		void registerCmd(string name, void (Settings::*pt2Func)(const string&));
		void registerCmd(string name, void (Critterselection::*pt2Func)());
		void registerCmd(string name, void (Critterselection::*pt2Func)(const unsigned int&));

		void decreaseenergy();
		void increaseenergy();
		void decreasefoodmaxenergy();
		void increasefoodmaxenergy();
		void dec_worldsizex();
		void inc_worldsizex();
		void dec_worldsizey();
		void inc_worldsizey();
		void dec_worldsizez();
		void inc_worldsizez();
		void selectCritterAll();
		void selectCritter(const unsigned int& c);

		void camera_moveup();
		void camera_movedown();
		void camera_moveforward();
		void camera_movebackward();
		void camera_moveleft();
		void camera_moveright();
		void camera_lookup();
		void camera_lookdown();
		void camera_lookleft();
		void camera_lookright();
		void camera_rollleft();
		void camera_rollright();
		void camera_lookhorizontal();
		void camera_lookvertical();
		void camera_movehorizontal();
		void camera_movevertical();
		
		map<string, cmd*> cmdlist;
		typedef map <string, cmd*>::const_iterator cmdlist_iterator;
		cmdlist_iterator cmdit;
};

#endif
