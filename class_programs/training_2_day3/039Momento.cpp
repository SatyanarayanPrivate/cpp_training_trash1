#include<iostream>
#include<map>
#include<string>
using namespace std;

namespace nm39
{
	class IMomento
	{
	public:
		virtual map<string, string> Hydrate() = 0;
		virtual void DeHydrate(map<string, string> par) = 0;
	};

	class Person :public IMomento
	{
	public:
		string Name;
		string Age;
		string Salary;
		void DisplayPerson()
		{
			cout << "Name=" << Name << endl;
			cout << "Age=" << Age << endl;
			cout << "Salary=" << Salary << endl;
			cout << "______________________" << endl;
		}
		map<string, string> Hydrate()
		{
			map<string, string> temp;
			temp["Name"] = Name;
			temp["Age"] = Age;
			temp["Salary"] = Salary;
			return temp;
		}
		void DeHydrate(map<string, string> par)
		{
			this->Name = par["Name"];
			this->Age = par["Age"];
			this->Salary = par["Salary"];
		}
	};

	class Customer :public IMomento
	{
	public:
		string CustId;
		string CustType;
		string HWC;
		string CustName;
		map<string, string> Hydrate()
		{
			map<string, string> temp;
			temp["CustId"] = CustId;
			temp["CustType"] = CustType;
			temp["HWC"] = HWC;
			temp["CustName"] = CustName;
			return temp;
		}
		void DeHydrate(map<string, string> par)
		{
			this->CustId = par["CustId"];
			this->CustType = par["CustType"];
			this->HWC = par["HWC"];
			this->CustName = par["CustName"];
		}
		void DisplayCutomer()
		{
			cout << "CustId=" << CustId << endl;
			cout << "CustType=" << CustType << endl;
			cout << "HWC=" << HWC << endl;
			cout << "CustName=" << CustName << endl;
			cout << "______________________" << endl;
		}
	};

	class Momento
	{
		map<string, map<string, string>> MyMap;//c++11
	public:
		void SetMomento(string key, map<string, string> mapPar)
		{
			MyMap[key] = mapPar;
		}
		map<string, string> GetMomento(string key)
		{
			return MyMap[key];
		}
	};

	class CareTaker
	{
		Momento momento;
	public:
		void Add(string key, map<string, string> par)
		{
			momento.SetMomento(key, par);
		}

		map<string, string> Get(string key)
		{
			return momento.GetMomento(key);
		}
	};

	void main()
	{
		Person John;
		John.Name = "Jhonson";
		John.Age = "30";
		John.Salary = "500";


		Person Peter;
		Peter.Name = "Peter";
		Peter.Age = "35";
		Peter.Salary = "505";

		Customer Arvind;
		Arvind.CustId = "101";
		Arvind.CustName = "Kejri";
		Arvind.HWC = "True";
		Arvind.CustType = "Regular";

		CareTaker caretaker;
		caretaker.Add("John", John.Hydrate());
		caretaker.Add("Peter", Peter.Hydrate());
		caretaker.Add("Arvind", Arvind.Hydrate());

		Peter.Name = "Shilton";
		John.Name = "Michel";
		Arvind.CustName = "Kejrival";

		Peter.DisplayPerson();
		John.DisplayPerson();
		Arvind.DisplayCutomer();

		Peter.DeHydrate(caretaker.Get("Peter"));

		Peter.DisplayPerson();
		John.DisplayPerson();
		Arvind.DisplayCutomer();
	}
}