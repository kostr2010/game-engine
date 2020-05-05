#ifndef __SYS_DIN__
#define __SYS_DIN__

class MyClass {
public:
  MyClass();

  /* use virtual otherwise linker will try to perform static linkage */
  virtual void DoSomething();

private:
  int x;
};

#endif