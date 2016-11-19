#include<iostream>
using namespace std;
namespace nm40
{
	class Bank;
	class SbAccount;
	class CurrentAccount;
	class DmatAccount;

	class IHelper
	{
	public:
		virtual void DoInject(Bank*) = 0;
		virtual void DoInject(SbAccount*) = 0;
		virtual void DoInject(CurrentAccount*) = 0;
		virtual void DoInject(DmatAccount*) = 0;
	};

	class Bank
	{
	protected:
		static IHelper *hlp;
		Bank()
		{
		}
	public:
		static void Attach(IHelper *par)
		{
			hlp = par;
		}
	};

	IHelper * Bank::hlp;

	class SbAccount :public Bank
	{
	public:
		SbAccount()
		{

		}
		void DoSbJob()
		{
			cout << "Sb account business started " << endl;
			hlp->DoInject(this);
			cout << "Sb account business completed " << endl;
		}
	};

	class CurrentAccount :public Bank
	{
	public:
		CurrentAccount()
		{

		}
		void DoCurrentJob()
		{
			cout << "Current account business started " << endl;
			hlp->DoInject(this);
			cout << "Current account business completed " << endl;
		}
	};

	class DmatAccount :public Bank
	{
	public:
		DmatAccount()
		{
		}
		void DoDmatJob()
		{
			cout << "Dmat account business started " << endl;
			hlp->DoInject(this);
			cout << "Dmat account business completed " << endl;
		}
	};
	//--------------------------------------

	class MyInjector :public IHelper
	{
	public:
		virtual void DoInject(Bank*)
		{
			cout << "General job from customer for Bank" << endl;
		}
		virtual void DoInject(SbAccount*)
		{
			cout << "SB job from customer for (SbAccount)" << endl;
		}
		virtual void DoInject(CurrentAccount*)
		{
			cout << "Current job from customer for (Current)" << endl;
		}
		virtual void DoInject(DmatAccount*)
		{
			cout << "Dmat job from customer for (Dmat)" << endl;
		}
	};

	void main()
	{
		SbAccount sb;
		CurrentAccount curr;
		DmatAccount dm;
		Bank::Attach(new MyInjector());
		sb.DoSbJob();
		cout << "_____________________" << endl;
		curr.DoCurrentJob();
		cout << "_____________________" << endl;
		dm.DoDmatJob();
		cout << "_____________________" << endl;
	}
}