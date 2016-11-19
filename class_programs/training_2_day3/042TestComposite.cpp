#include<iostream>
#include<string>
#include<vector>
using namespace std;
namespace nm42
{
	struct IPlayerBase
	{
		virtual void DisplayPlayer() = 0;
	};
	struct IPlayer :IPlayerBase
	{
		string Name;
	};
	struct ITeamBase
	{
		virtual void DisplayTeam() = 0;
	};
	struct ITeam :ITeamBase
	{
		string Name;
		virtual void AddPlayer(IPlayer *pl) = 0;
	};
	struct IDivsionBase
	{
		virtual void DisplayDivision() = 0;
	};
	struct IDivsion :IDivsionBase
	{
		string Name;
		virtual void AddTeam(ITeam *tm) = 0;
	};

	struct ILeagueBase
	{
		virtual void DisplayLeague() = 0;
	};
	struct ILeague :ILeagueBase
	{
		string Name;

		virtual void AddDivision(IDivsion *pl) = 0;
	};

	void DoJob(ILeagueBase *il)
	{
		cout << "Job Started ..." << endl;
		il->DisplayLeague();
		cout << "Job Completed ..." << endl;
	}

	void DoJob(IDivsionBase *div)
	{
		cout << "Job Started for division ..." << endl;
		div->DisplayDivision();
		cout << "Job Completed division..." << endl;
	}

	struct Player :IPlayer
	{
		Player(string Name)
		{
			this->Name = Name;
		}
		virtual void DisplayPlayer()
		{
			cout << "\t\t\t" << Name << endl;
		}
	};

	struct PLayerList :vector < IPlayer* >, IPlayerBase
	{

		virtual void DisplayPlayer()
		{
			for (size_t i = 0; i < (*this).size(); i++)
			{
				(*this)[i]->DisplayPlayer();
			}
		}
	};


	struct Team :ITeam
	{
		PLayerList list;
		Team(string Name)
		{
			this->Name = Name;
		}
		virtual void AddPlayer(IPlayer *pl)
		{
			list.push_back(pl);
		}
		virtual void DisplayTeam()
		{
			cout << "\t\t" << Name << endl;
			list.DisplayPlayer();
		}
	};

	struct TeamList :vector<ITeam*>, ITeamBase
	{
		virtual void DisplayTeam()
		{
			for (size_t i = 0; i < (*this).size(); i++)
			{
				(*this)[i]->DisplayTeam();
			}
		}
	};

	struct Division :IDivsion
	{
		TeamList list;
		Division(string Name)
		{
			this->Name = Name;
		}
		virtual void AddTeam(ITeam *tm)
		{
			list.push_back(tm);
		}
		virtual void DisplayDivision()
		{
			cout << "\tDivision " << Name << endl;
			list.DisplayTeam();
		}
	};

	struct DivisionList :vector <IDivsion*>, IDivsionBase
	{
		DivisionList()
		{
		}
		void DisplayDivision()
		{
			for (size_t i = 0; i < (*this).size(); i++)
			{
				(*this)[i]->DisplayDivision();
			}
		}
	};

	struct League :ILeague
	{
		DivisionList list;
		League(string Name)
		{
			this->Name = Name;
		}

		void AddDivision(IDivsion *div)
		{
			this->list.push_back(div);
		}
		void DisplayLeague()
		{
			cout << "League " << Name << endl;
			list.DisplayDivision();
		}
	};

	struct LeagueList :vector <ILeague*>, ILeagueBase
	{
		LeagueList()
		{
		}
		void AddLeague(ILeague *il)
		{
			this->push_back(il);
		}

		void DisplayLeague()
		{

			for (size_t i = 0; i < (*this).size(); i++)
			{
				(*this)[i]->DisplayLeague();
			}
		}
	};


	void main()
	{
		LeagueList list;
		League *il;
		list.AddLeague(il = new League("A"));
		Division *id;
		il->AddDivision(id = new Division("X"));
		ITeam *it;
		id->AddTeam(it = new Team("Team Apple"));
		it->AddPlayer(new Player("Sachin"));
		it->AddPlayer(new Player("Rahul"));
		it->AddPlayer(new Player("Sewag"));
		it->AddPlayer(new Player("Zaheer"));
		id->AddTeam(it = new Team("Team Orange"));
		it->AddPlayer(new Player("Ponting"));
		it->AddPlayer(new Player("Clark"));
		it->AddPlayer(new Player("Waugh"));
		it->AddPlayer(new Player("Gilly"));
		id->AddTeam(new Team("Team Pine"));
		id->AddTeam(new Team("Team Jack"));
		id->AddTeam(new Team("Team Mango"));
		il->AddDivision(id = new Division("Y"));
		id->AddTeam(new Team("Team North"));
		id->AddTeam(new Team("Team East"));
		id->AddTeam(new Team("Team West"));
		id->AddTeam(new Team("Team South"));

		il->AddDivision(id = new Division("Z"));
		id->AddTeam(new Team("Team Spade"));
		id->AddTeam(new Team("Team Hearts"));
		id->AddTeam(new Team("Team Club"));
		id->AddTeam(new Team("Team Diamond"));
		id->AddTeam(new Team("Team Joker"));


		list.AddLeague(il = new League("B"));
		il->AddDivision(id = new Division("Alpha"));
		id->AddTeam(new Team("Team Bangalore"));
		id->AddTeam(new Team("Team Hyderabad"));
		id->AddTeam(new Team("Team Delhi"));
		id->AddTeam(new Team("Team Noida"));
		id->AddTeam(new Team("Team Chennai"));
		il->AddDivision(id = new Division("Beta"));
		id->AddTeam(new Team("Team Congress"));
		id->AddTeam(new Team("Team BJP"));
		id->AddTeam(new Team("Team AAP"));
		id->AddTeam(new Team("Team JD"));
		id->AddTeam(new Team("Team AIADMK"));
		il->AddDivision(id = new Division("Gamma"));
		id->AddTeam(new Team("Team India"));
		id->AddTeam(new Team("Team Bangladesh"));
		id->AddTeam(new Team("Team Zimbabwe"));
		id->AddTeam(new Team("Team WI"));
		id->AddTeam(new Team("Team Australia"));
		DoJob(&list);
	}
}