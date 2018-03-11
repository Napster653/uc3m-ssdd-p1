#include "claves.c"

int main ()
{
	printf ("init\n");
	init ();
	printf ("init finished\n\n");

	printf ("set\n");
	set_value (1, "test1", 11.1);
	printf("set finished\n\n");

	printf ("set\n");
	set_value (2, "test2", 22.2);
	printf ("set finished\n\n");

	printf ("get\n");
	char valor1[256];
	float valor2;
	get_value (1, valor1, &valor2);
	printf ("%s\n", valor1);
	printf ("%f\n", valor2);
	printf ("get finished\n\n");

	printf ("get\n");
	get_value (2, valor1, &valor2);
	printf ("%s\n", valor1);
	printf ("%f\n", valor2);
	printf ("get finished\n\n");

	printf ("closeQueue\n");
	closeQueue ();
	printf ("closeQueue finished\n\n");
	return 0;
}
