#include <goto-programs/goto_functions.h>
#include <goto-programs/goto_program.h>
#include <util/context.h>
#include <stdint.h>
#include <vector>
#include <random>

using u32 = uint_least32_t;
using engine = std::mt19937;

class goto_mutationt
{
public:
  goto_mutationt(uint8_t *Data, size_t Size,goto_functionst &func)
  {
    this->Data = Data;
    this->Size = Size;
    this->seeds = NULL;
    getMain(this->m_it,func);
  }
  bool mutateSequence(messaget &msg,goto_functionst &func);
  bool mutateNonSequence(messaget &msg,goto_functionst &func);
  void getMain(goto_functionst::function_mapt::iterator &m_it, goto_functionst& func);

  void setSeeds(goto_programt &mmain);
  void setPseudoSeeds(goto_programt &mmain);
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
  goto_functionst::function_mapt::iterator m_it ;

private:
  uint8_t *Data=NULL;
  size_t Size;
  uint16_t *seeds;
};
