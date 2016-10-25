namespace Ex7
{
	void __cdecl fun(int i,int j)
	{
	}//ret	0

	void __stdcall fun2(int i,int j)
	{
	}//ret	8

	void __fastcall fun3(int i,int j)
	{
	}//ret	0
	class CA
	{
	public:
		void __thiscall fun4(int i,int j)
		{
		}//ret	8
	};
};
using namespace Ex7;

int main()
{
	CA obj;
	obj.fun4(10,20);
	/*
	push	20					
	push	10					
	lea	ecx, DWORD PTR _obj$[ebp]
	call	?fun4@CA@@QAEXHH@Z			
	*/
	
	
	
	
	
	fun(10,20);
	/*
	push	20					
	push	10					
	call	?fun@@YAXHH@Z				
	add	esp, 8
	*/
	fun2(10,20);
	/*
	push	20					
	push	10					
	call	?fun2@@YGXHH@Z				
	*/





	fun3(10,20);
	/*
	mov	edx, 20					
	mov	ecx, 10					
	call	?fun3@@YIXHH@Z				
	*/
    
    return 0;
}