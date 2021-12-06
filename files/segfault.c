#include <sys/types.h>
#include <signal.h>

int	main(void)
{
	kill(0, SIGABRT);
	return (0);
}
