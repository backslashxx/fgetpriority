#include <stdint.h>
#include "small_rt.h"
#define syscall __syscall

#define __AARCH64_shitcall	42

#define gp_magic1		0x11111111	// arg0
#define gp_flag_enable		0x1
#define gp_flag_disable		0x2
#define gp_flag_reset		0x3
#define gp_flag_setall		0x4

#define isdigit(x) ((x) >= '0' && (x) <= '9')
static long dumb_atol(const char *str)
{
	long res = 0;
	if (!str || !*str)
		return res;
start:
	if (!isdigit((unsigned char)*str))
		return res;

	res = (res * 10) + (*str - 48);
	str++;
	if (*str)
		goto start;

	return res;
}
#define atol dumb_atol

static void print_out(const char *buf, unsigned long len)
{
	__syscall(SYS_write, 1, (long)buf, len);
}

#define memcmp __builtin_memcmp

static int main(int argc, char **argv, char **envp)
{
	const char ok[] = { 'o', 'k', '\n'};
	uintptr_t confirm; // confirm receipt here
	uintptr_t command;
	uintptr_t uid = 0;

	if (!argv[1])
		__builtin_trap();

	if (!memcmp(argv[1], "enable", sizeof("enable")))
		command = gp_flag_enable;

	if (!memcmp(argv[1], "disable", sizeof("disable")))
		command = gp_flag_disable;

	if (!memcmp(argv[1], "reset", sizeof("reset")))
		command = gp_flag_reset;

	if (!memcmp(argv[1], "setall", sizeof("setall")))
		command = gp_flag_setall;

	if (!argv[2] && command != gp_flag_reset && command != gp_flag_setall)
		__builtin_trap();

	if (argv[2]) {
		uid = atol(argv[2]);
		if (uid > 20000 || uid < 10000)
			__builtin_trap();
	}

	syscall(__AARCH64_shitcall, gp_magic1, command, uid, 0, 0, &confirm);

	if ((uintptr_t)&confirm == confirm)
		print_out(ok, sizeof(ok));
	else
		__builtin_trap();

	return 0;
}
