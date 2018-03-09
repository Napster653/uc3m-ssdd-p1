#include "claves.c"

int main ()
{
	printf ("init\n");
	init ();
	printf ("init finished\n");

	printf ("set\n");
	set_value (4, "hola", 15.6);
	printf("set finished\n");

	printf ("get\n");
	char valor1[256];
	float valor2;
	get_value (4, valor1, &valor2);
	printf("%s\n", valor1);
	printf("%f\n", valor2);
	printf("get finished\n");

	printf ("closeQueue\n");
	closeQueue ();
	printf ("closeQueue finished\n");
	return 0;
}