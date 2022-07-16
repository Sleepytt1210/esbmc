#include <goto-programs/goto_functions.h>
#include <goto-programs/goto_program.h>
#include <stdint.h>

class mutationt
{
public:
  mutationt(uint8_t *Data, size_t Size)
  {
    this->Data = Data;
    this->Size = Size;
  }
  bool mutateValue(goto_functionst &func, messaget &msg);
  bool mutateSequence(goto_functionst &func, messaget &msg);
  bool mutateNonSequence(goto_functionst &func, messaget &msg);

private:
  uint8_t *Data;
  size_t Size;
};
