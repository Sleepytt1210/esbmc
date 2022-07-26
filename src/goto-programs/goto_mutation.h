#include <goto-programs/goto_functions.h>
#include <goto-programs/goto_program.h>
#include <util/context.h>
#include <stdint.h>
#include <vector>

class goto_mutationt
{
public:
  goto_mutationt(uint8_t *Data, size_t Size, goto_functionst &func)
  {
    this->Data = Data;
    this->Size = Size;
    this->func = func;
    this->seeds = NULL;
  }
  bool mutateSequence(messaget &msg);
  bool mutateNonSequence(messaget &msg);
  void getMain(goto_functionst::function_mapt::iterator &m_it);
  static void
  getMain(goto_functionst::function_mapt::iterator &m_it, goto_functionst func)
  {
    m_it = func.function_map.find("c:@F@main");
  }

  void setSeeds(goto_programt &mmain);
  bool hasSeeds();
  static void
  output(goto_programt &mmain, std::ostringstream &os, messaget &msg)
  {
    forall_goto_program_instructions(it, mmain)
    {
      (*it).output_instruction(
        *migrate_namespace_lookup, "c:@F@main", os, msg, false);
    }
  }

private:
  uint8_t *Data;
  size_t Size;
  goto_functionst func;
  uint16_t *seeds;
};
