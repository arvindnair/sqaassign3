#include "pin++/Callback.h"
#include "pin++/Pintool.h"
#include "pin++/Buffer.h"
#include "pin++/Trace_Instrument.h"
#include "pin++/Instruction_Instrument.h"

class printip : public OASIS::Pin::Callback < printip (OASIS::Pin::ARG_INST_PTR) >
{
public:
  printip (FILE * file)
    : file_ (file) { }

  void handle_analyze (param_type1 addr)
  {
    ::fprintf (this->file_, "0x%p\n", addr);
  }

private:
  FILE * file_;
};

class Instrument : public OASIS::Pin::Instruction_Instrument <Instrument>
{
public:
  Instrument (FILE * file)
    : printip_ (file) { }

  void handle_instrument (const OASIS::Pin::Ins & ins)
  {
    this->printip_.insert (IPOINT_BEFORE, ins);
  }

private:
  printip printip_;
};

class my_data_callback : public OASIS::Pin::Tool <my_data_callback>
{
public:
  my_data_callback (void)
    : file_ (fopen ("my_data_callback.out", "w")),
      inst_ (file_)
  {
    this->enable_fini_callback ();
  }


  void handle_fini (INT32)
  {
    fprintf (this->file_, "#eof\n");
    fclose (this->file_);
  }

private:
  FILE * file_;
  Instrument inst_;
};

DECLARE_PINTOOL (my_data_callback);