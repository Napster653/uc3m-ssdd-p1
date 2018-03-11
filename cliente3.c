#include "claves.c"

int main ()
{
	printf ("Init...");
	init ();
	printf ("Done!\n\n");

	printf ("Set...");
	set_value (1, "test1", 11.1);
	printf ("Done!\n\n");

	printf ("Set...");
	set_value (2, "test2", 22.2);
	printf ("Done!\n\n");

	printf ("Num...");
	printf ("\t%d\t", num_items ());
	printf ("Done!\n\n");

	printf ("Delete...");
	delete_key (2);
	printf ("Done!\n\n");

	printf ("Num...");
	printf ("\t%d\t", num_items ());
	printf ("Done!\n\n");


	printf ("CloseQueue...");
	closeQueue ();
	printf ("Done!\n\n");
	return 0;
}
