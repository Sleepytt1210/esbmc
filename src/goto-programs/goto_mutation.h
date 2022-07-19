#include <goto-programs/goto_functions.h>
#include <goto-programs/goto_program.h>
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
  bool mutateValue(messaget &msg);
  bool mutateSequence(messaget &msg);
  bool mutateNonSequence(messaget &msg);
  void getMain(goto_functionst::function_mapt::iterator &m_it);
  void setSeeds(goto_programt &mmain);
  bool hasSeeds();
  void output(goto_programt &mmain, std::ostringstream &os, messaget &msg);

private:
  uint8_t *Data;
  size_t Size;
  goto_functionst func;
  uint16_t *seeds;
};
