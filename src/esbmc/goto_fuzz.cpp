#include <esbmc/goto_fuzz.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
  // roll back
  (*goto_ptr).goto_functions = roll_back_func;

  messaget msg;
  uint8_t *t = (uint8_t *)Data;
  goto_mutationt mutation(t, Size, (*goto_ptr).goto_functions);
  if(mutation.m_it != roll_back_func.function_map.end())
  {
    goto_programt &mmain = mutation.m_it->second.body;
    int program_len = mmain.instructions.size();
    if(program_len + 1 >= Size)
      return -1; // Rejecting unwanted inputs
  }
  mutation.mutateSequence(msg, (*goto_ptr).goto_functions);
  mutation.mutateNonSequence(msg, (*goto_ptr).goto_functions);

  (*goto_ptr).doit_fuzz();
  return 0;
}

void goto_fuzz::fuzz_init(
  esbmc_parseoptionst *parseoptions)
{
  goto_ptr = parseoptions;
  roll_back_func = (*parseoptions).goto_functions;
  char str[100];
  sprintf(str,"-max_total_time=%d",fuzz_timeout);
  printf("str %s",str);
  fargc = 5;
  fargv = new char *[5];
  fargv[0] = "./esbmc";
  fargv[1] = "-seed=1";
  fargv[2] = "corpus";
  fargv[3] = "seeds";
  fargv[4] = str;

  int seeds_num = 10;
  messaget msg;
  for(int i = 0; i < seeds_num; i++)
  {
    (*parseoptions).goto_functions = roll_back_func;

    goto_mutationt mutation(NULL, 0, (*parseoptions).goto_functions);
    mutation.mutateSequence(msg, (*parseoptions).goto_functions);
    mutation.mutateNonSequence(msg, (*parseoptions).goto_functions);
  }
}
