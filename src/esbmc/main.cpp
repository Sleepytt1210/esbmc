/*******************************************************************\

Module: Main Module

Author: Lucas Cordeiro, lcc08r@ecs.soton.ac.uk
		Jeremy Morse, jcmm106@ecs.soton.ac.uk

\*******************************************************************/

/*

  ESBMC
  SMT-based Context-Bounded Model Checking for ANSI-C/C++
  Copyright (c) 2009-2011, Lucas Cordeiro, Federal University of Amazonas
  Jeremy Morse, Denis Nicole, Bernd Fischer, University of Southampton,
  Joao Marques Silva, University College Dublin.
  All rights reserved.

*/

#include <cstdint>
#include <stdint.h>
#include <stdio.h>
#include <esbmc/esbmc_parseoptions.h>
#include <langapi/mode.h>
#include <util/message/default_message.h>
#include <irep2/irep2.h>
#include <goto-programs/goto_mutation.h>

static esbmc_parseoptionst *ptr = NULL;
static goto_functionst func;

extern "C" int LLVMFuzzerRunDriver(
  int *argc,
  char ***argv,
  int (*UserCb)(const uint8_t *Data, size_t Size));

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
  // roll back
  (*ptr).goto_functions = func;

  messaget msg;
  uint8_t *t = (uint8_t *)Data;
  goto_mutationt mutation(t, Size, (*ptr).goto_functions);
  if(mutation.m_it != func.function_map.end())
  { 
    goto_programt &mmain = mutation.m_it->second.body;
    int program_len = mmain.instructions.size();
    if(program_len + 1 >= Size)
      return -1; // Rejecting unwanted inputs
  }
  mutation.mutateSequence(msg, (*ptr).goto_functions);
  mutation.mutateNonSequence(msg, (*ptr).goto_functions);

  (*ptr).doit_fuzz();
  return 0;
}

int main(int argc, const char **argv)
{
  // Initialize
  //char **aargv = (char **)argv;
  messaget msg;
  esbmc_parseoptionst parseoptions(argc, argv, msg);
  parseoptions.main();

  if(parseoptions.cmdline.isset("goto-libfuzz"))
  {
    ptr = &parseoptions;
    func = (*ptr).goto_functions;

    int aargc = 6;
    char **aargv = new char *[6];
    aargv[0] = "./esbmc";
    aargv[1] = "-max_total_time=60";

    aargv[2] = "-seed=1";
    aargv[3] = "corpus";
    aargv[4] = "old_corpus";
    aargv[5] = "-runs=10000";
    LLVMFuzzerRunDriver(&aargc, &aargv, LLVMFuzzerTestOneInput);
  }
}
