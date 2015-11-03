#ifndef __PROCESS_H
#define __PROCESS_H

class Mouse;

enum Pstat{ p_menu, p_game };

class Process{
protected:
	Mouse* mouse;

public:
	const static int NUM_STAT = 2;

public:
	Process();
	Process(Mouse*);
	~Process();

	void InitList(Process***, Process**) const;

	//virtual void Init(int);
	virtual void Init();
	virtual void Loop() const;

	Mouse* get_mouse() const{ return mouse; }	// virtual??
};

#endif // __PROCESS_H