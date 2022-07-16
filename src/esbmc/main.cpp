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
#include <esbmc/esbmc_parseoptions.h>
#include <langapi/mode.h>
#include <util/message/default_message.h>
#include <irep2/irep2.h>

extern "C" int LLVMFuzzerRunDriver(
  int *argc,
  char ***argv,
  int (*UserCb)(const uint8_t *Data, size_t Size, int argc, const char **argv));

extern "C" int LLVMFuzzerTestOneInput(
  const uint8_t *Data,
  size_t Size,
  int argc,
  const char **argv)
{
  messaget msg;
  esbmc_parseoptionst parseoptions(argc, argv, msg);
  parseoptions.setFuzz(Data, Size);
  return parseoptions.main();
}

int main(int argc, const char **argv)
{
  char **aargv = (char **)argv;
  LLVMFuzzerRunDriver(&argc, &aargv, LLVMFuzzerTestOneInput);
}
