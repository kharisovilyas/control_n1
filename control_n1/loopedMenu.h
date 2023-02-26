#pragma once

/*
#ifndef LOOPEDMENU_H
#define LOOPEDMENU_H
*/

namespace menu {

	class loopedMenu{
	public:
		const int file = 1;
		const int console = 2;
		const int returnp = 3;
		const int task1 = 4;
		const int task2 = 5;
		const int task3 = 6;
		const int exitp = 7;
		
	public:
		void printInputWays();
		void printAction();
		void launchMenu();
		void selectTask();
	};
}


//#endif /* LOOPEDMENU_H */