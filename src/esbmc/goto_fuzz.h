#include <cstdint>
#include <stdint.h>
#include <stdio.h>
#include <esbmc/esbmc_parseoptions.h>
#include <langapi/mode.h>
#include <util/message/default_message.h>
#include <irep2/irep2.h>
#include <goto-programs/goto_mutation.h>

static esbmc_parseoptionst *goto_ptr=NULL;
static goto_functionst roll_back_func;

extern "C" int LLVMFuzzerRunDriver(
  int *argc,
  char ***argv,
  int (*UserCb)(const uint8_t *Data, size_t Size));

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size);

class goto_fuzz
{
public:
  goto_fuzz()
  {
  }

  void fuzz_init(esbmc_parseoptionst *parseoptions);

  int fargc;
  char **fargv;
};