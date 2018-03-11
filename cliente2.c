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

	printf ("Set...");
	if (set_value (3, "test33333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333", 33.3) < 0)
	{
		printf ("Error!\n\n");
	}
	else
	{
		printf ("Done!\n\n");
	}

	char valor1[256];
	float valor2;
	printf ("Get...");
	get_value (1, valor1, &valor2);
	printf ("Done!\n");
	printf ("%s\n", valor1);
	printf ("%f\n\n", valor2);

	printf ("Get...");
	get_value (2, valor1, &valor2);
	printf("Done!\n");
	printf ("%s\n", valor1);
	printf ("%f\n\n", valor2);

	printf ("Delete...");
	delete_key (2);
	printf ("Done!\n\n");

	printf ("Get...");
	get_value (1, valor1, &valor2);
	printf ("Done!\n");
	printf ("%s\n", valor1);
	printf ("%f\n\n", valor2);

	printf ("Get...");
	if (get_value (2, valor1, &valor2) < 0)
	{
		printf("Error!\n\n");
	}
	else
	{
		printf ("Done!\n");
		printf ("%s\n", valor1);
		printf ("%f\n\n", valor2);
	}

	printf ("CloseQueue...");
	closeQueue ();
	printf ("Done!\n\n");
	return 0;
}
