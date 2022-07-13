#include <goto-programs/goto_functions.h>
#include <goto-programs/goto_program.h>

class mutationt
{
public:
  void mutateValue(goto_functionst &func, messaget &msg);
  static bool mutateSequence(goto_functionst &func, messaget &msg);
  void mutateNonSequence(goto_functionst &func, messaget &msg);
};


