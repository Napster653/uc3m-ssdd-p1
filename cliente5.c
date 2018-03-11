#include "claves.c"

int main ()
{
	printf ("Init...");
	init ();
	printf ("Done!\n\n");

	printf ("Set loop starting...");
	char word[256];
	for (int i = 0; i < 1000; ++i)
	{
		sprintf (word, "test-%d", i);
	 	set_value (i, word, (float)i);
	}
	printf ("Done!\n\n");

	printf ("Num...");
	printf ("\t%d\t", num_items ());
	printf ("Done!\n\n");

	printf ("CloseQueue...");
	closeQueue ();
	printf ("Done!\n\n");
	return 0;
}
