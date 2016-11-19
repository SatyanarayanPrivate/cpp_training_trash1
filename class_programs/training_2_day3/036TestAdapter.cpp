#include<iostream>
using namespace std;

namespace nm36
{

	/*class KeyBoardEvents
	{
	public:
	void ReturnKeyPress()
	{
	cout << "Enter KeyPressed" << endl;
	}
	void CtrlArrow()
	{
	cout << "Item moved from current location" << endl;
	}

	};*/

	class MouseEvents
	{
	public:
		void ClickEvent()
		{
			cout << "Element Selected for operation" << endl;
		}
		void DragEvent()
		{
			cout << "Element getting draged in this direction" << endl;
		}
	};


	class KeyBoardEvents
	{
		MouseEvents mouse;
	public:
		void ReturnKeyPress()
		{
			mouse.ClickEvent();
		}
		void CtrlArrow()
		{
			mouse.DragEvent();
		}

	};
	void main()
	{
		KeyBoardEvents kb;
		kb.ReturnKeyPress();
		kb.CtrlArrow();
	}
}