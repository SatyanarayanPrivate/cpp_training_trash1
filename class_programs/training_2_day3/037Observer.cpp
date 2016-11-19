#include<iostream>
#include<string>
using namespace std;
namespace nm37
{
	class Observer
	{
	public:
		virtual void Update() = 0;
	};

	class ISubscriber
	{
	public:
		virtual void RecieveUpdate(string str) = 0;
	};

	class ESPN :public ISubscriber
	{
	public:
		virtual void RecieveUpdate(string str)
		{
			cout << "*************ESPN **** " << str << endl;
		}
	};
	class StarSports :public ISubscriber
	{
	public:
		virtual void RecieveUpdate(string str)
		{
			cout << "*************StarSports =========> " << str << endl;
		}
	};
	class DDNews :public ISubscriber
	{
	public:
		virtual void RecieveUpdate(string str)
		{
			cout << "&&&&&&&&&&&&&&&&&&DDNews **** " << str << endl;
		}
	};
	class List
	{
		static List *head;
		List *next;
		Observer *obs;
	public:
		List(Observer *obs) :obs(obs)
		{
			next = head;
			head = this;
		}
		static void Notify()
		{
			for (List *trav = head; trav != NULL; trav = trav->next){
				trav->obs->Update();
			}
		}
	};
	List * List::head = NULL;

	class Subject
	{
	public:
		void Attach(Observer *obs)
		{
			new List(obs);
		}
		void Detach()
		{

		}
		void Notify()
		{
			List::Notify();
		}
	};



	class ConcreteSubject :public Subject
	{
		string _subjectState;
	public:
		void SetSubjectState(string str)
		{
			_subjectState = str;
		}
		string GetSubjectState()
		{
			return _subjectState;
		}
	};


	class ConcreteObserver :public Observer
	{
		ISubscriber *_name;
		string _observerState;
		ConcreteSubject *_subject;
	public:
		ConcreteObserver(ConcreteSubject *subject, ISubscriber *name) :_subject(subject), _name(name)
		{
		}
		void Update() override//c++11
		{
			_observerState = _subject->GetSubjectState();
			_name->RecieveUpdate(_observerState);
			//cout << "Observer " << _name << "'s new state is " << _observerState << endl;
		}
		ConcreteSubject* GetSubject()
		{
			return _subject;
		}
		void SetSubject(ConcreteSubject *value){
			_subject = value;
		}
	};
	void main()
	{
		ConcreteSubject *cs = new ConcreteSubject();
		cs->Attach(new ConcreteObserver(cs, new ESPN()));
		cs->Attach(new ConcreteObserver(cs, new DDNews()));
		cs->Attach(new ConcreteObserver(cs, new StarSports()));
		cs->SetSubjectState(" (Sachin Scored 50) ");
		cs->Notify();
	}
}