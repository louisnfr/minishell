#include <sys/types.h>
#include <signal.h>

int	main(void)
{
	kill(0, SIGTRAP);
	return (0);
}
