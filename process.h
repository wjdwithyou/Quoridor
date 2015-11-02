#ifndef __PROCESS_H
#define __PROCESS_H

enum Pstat{ p_menu, p_game };

class Process{
public:
	const static int NUM_STAT = 2;

public:
	Process();
	~Process();

	void InitList(Process***, Process**) const;

	virtual void Init(int);
	virtual void Loop() const;
};

#endif // __PROCESS_H