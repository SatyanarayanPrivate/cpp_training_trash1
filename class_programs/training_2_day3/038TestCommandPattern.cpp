#include<iostream>
#include<vector>
#include<string>
using namespace std;

namespace nm38
{
	class Calculator
	{
	private:
		int _curr = 0;

	public:
		void Operation(char opr, int operand)
		{
			switch (opr)
			{
			case '+':_curr += operand; break;
			case '-':_curr -= operand; break;
			case '*':_curr *= operand; break;
			case '/':_curr /= operand; break;
			};
			cout << "Current value = " << _curr << " (following " << opr << " " << operand << ")" << endl;
		}
	};

	class Command
	{
	public:
		virtual void Execute() = 0;
		virtual void UnExecute() = 0;
	};

	class CalculatorCommand :public Command
	{
		char _operator;
		int _operand;
		Calculator *_calculator;

	public:
		CalculatorCommand(Calculator *calc, char opr, int operand) :_operator(opr), _operand(operand), _calculator(calc)
		{
			vector<string> vect;
			string str;
		}
		char Undo(char opr)
		{
			switch (opr)
			{
			case '+':return '-';
			case '-':return '+';
			case '*':return '/';
			case '/':return '*';
			};
			return ' ';

		}
		virtual void Execute()
		{
			_calculator->Operation(_operator, _operand);
		}
		virtual void UnExecute()
		{
			_calculator->Operation(Undo(_operator), _operand);
		}

	};


	class User
	{
		Calculator *calc = new Calculator();
		vector<Command*> _commands;
		int _current = 0;
	public:
		void Redo()
		{
			if (_current < _commands.size())
			{
				Command *command = _commands[_current++];
				command->Execute();
			}
		}
		void Undo()
		{
			if (_current > 0)
			{
				Command *command = _commands[--_current];
				command->UnExecute();

			}
		}
		void Compute(char opr, int operand)
		{
			Command*command = new CalculatorCommand(calc, opr, operand);
			command->Execute();

			_commands.push_back(command);
			_current++;
		}
	};

	void main()
	{
		User *user = new User();

		user->Compute('+', 100);
		user->Compute('+', 200);
		user->Compute('-', 100);
		user->Compute('/', 4);
		user->Compute('*', 4);

		user->Undo();
		user->Undo();
		user->Undo();
		user->Undo();
		user->Undo();
		cout << "_____________________" << endl;
		user->Redo();
	}

}
