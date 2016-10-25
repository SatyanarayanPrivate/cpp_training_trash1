namespace Ex2
{
	/* -------- prolog -----------
		push	ebp		//save callers frame base pointer
		mov	ebp, esp    //set current base pointer
		sub	esp, 192   //allocate memory for local variables
	*/
	void fun(int i,int j)
	{
	//----------- body -----------
	}
	/* --------- epilog ----------
		mov	esp, ebp	//remove local variables	
		pop	ebp			//reset base pointer
		ret	0			//return to caller
	*/
};
using namespace Ex2;
int main (void)
{
	fun(10,20);
/*
	push	20					
	push	10					
	call	?fun@@YAXHH@Z				
	add	esp, 8	//remove arguments from the stack
*/
}