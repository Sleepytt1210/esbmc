#include <goto-programs/goto_mutation.h>

int cnt = 0;

void goto_mutationt::createDir(std::string dir)
{
  if(access(dir.c_str(), 0) == -1)
  {
#ifdef WIN32
    int flag = mkdir(dir.c_str());
#else
    int flag = mkdir(dir.c_str(), S_IRWXU);
#endif
    if(flag != 0)
    {
      throw std::exception();
    }
  }
}

void goto_mutationt::getMain(
  goto_functionst::function_mapt::iterator &m_it,
  goto_functionst &func)
{
  m_it = func.function_map.find("c:@F@main");
}

bool goto_mutationt::hasSeeds()
{
  return (seeds == NULL ? false : true);
}

void goto_mutationt::setSeeds(goto_programt &mmain)
{
  int program_len = mmain.instructions.size();
  seeds = (uint16_t *)calloc(program_len, sizeof(uint16_t));
  for(size_t i = 0; i < program_len - 1 && i < Size - 2; i++)
  {
    seeds[i] = abs(((uint16_t)Data[i] << 8) | Data[i + 2]);
  }
}

void goto_mutationt::setPseudoSeeds(goto_programt &mmain)
{
  createDir("seeds");
  createDir("corpus");

  int program_len = mmain.instructions.size();
  uint16_t data[program_len];
  std::random_device os_seed;
  const u32 seed = os_seed();

  engine generator(seed);
  std::ofstream prn("seeds/" + std::to_string(cnt++), std::ios::out);
  std::uniform_int_distribution<u32> distribute(0, program_len - 1);
  for(auto d : data)
  {
    d = abs(uint16_t(distribute(generator)));
    prn << d;
  }
  seeds = data;
  prn.close();
}

template <typename T>
void Knuth_Shuffle(std::vector<T> &arr, uint16_t *seeds)
{
  int len = arr.size();
  for(int i = len - 1; i >= 0; i--)
  {
    //std::swap(*arr[i], *arr[seeds[i] % (i + 1)]);
    (*arr[i]).swap(*arr[seeds[i] % (i + 1)]);
  }
}

bool goto_mutationt::mutateSequence(
  messaget &msg,
  goto_functionst &func) //const uint8_t *data, size_t size,
{
  std::ostringstream os;
  if(m_it != func.function_map.end())
  {
    goto_programt &mmain = m_it->second.body;
    int program_len = mmain.instructions.size();
    if(!hasSeeds())
    {
      if(Data == NULL)
      {
        setPseudoSeeds(mmain);
      }
      else
      {
        setSeeds(mmain);
      }
    }
    std::vector<goto_programt::instructiont::targett> instructions;
    Forall_goto_program_instructions(it, mmain)
    {
      if((*it).type == END_FUNCTION)
      {
        continue;
      }
      instructions.push_back(it);
    }
    Knuth_Shuffle(instructions, seeds);

    os << "Show mutated sequence structure. \n";
    output(mmain, os, msg);
  }

  msg.status(os.str());
  return false;
}

bool goto_mutationt::mutateNonSequence(messaget &msg, goto_functionst &func)
{
  std::ostringstream os;
  if(m_it != func.function_map.end())
  {
    goto_programt &mmain = m_it->second.body;
    int program_len = mmain.instructions.size();
    if(!hasSeeds())
    {
      if(Data == NULL)
      {
        setPseudoSeeds(mmain);
      }
      else
      {
        setSeeds(mmain);
      }
    }
    std::vector<goto_programt::instructiont::targett> targets;
    Forall_goto_program_instructions(it, mmain)
    {
      if((*it).has_target())
      {
        targets.push_back((*it).get_target());
      }
    }
    Knuth_Shuffle(targets, seeds);
    os << "Show mutated non-sequence structure. \n";
    output(mmain, os, msg);
  }

  msg.status(os.str());
  return false;
}