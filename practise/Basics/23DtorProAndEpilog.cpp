namespace Ex29
{
	struct SA
	{
		~SA()
		{
			//******* prolog ****************
			/*
				PUSH EBP
				MOV EBP,ESP
				ADD ESP,40

				1.initialize virtual inheritance vptr

				2.initialize all virtual function vptr
			*/
			//******* body ****************
			/*
				programmer writes cleanup code
			*/
			//******* EPILOG ****************
			/*
				3.call all data members destructor
					in the reverse order of declaration
				
					m_c.IC::~IC();
					m_b.IB::~IB();
					m_a.IA::~IA();

				4.call all base class destructor
					in the reverse order of inheritance
					IZ::~IZ();
					IY::~IY();
					IX::~IX();

				  MOV ESP,EBP
				  pop EBP
				  ret
			*/
		}
	};
};
