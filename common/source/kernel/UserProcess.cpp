#include "ProcessRegistry.h"
#include "UserProcess.h"
#include "kprintf.h"
#include "Console.h"
#include "Loader.h"
#include "VfsSyscall.h"
#include "File.h"
#include "ArchMemory.h"
#include "PageManager.h"
#include "ArchThreads.h"
#include "offsets.h"

UserProcess::UserProcess(ustl::string filename, FileSystemInfo *fs_info, uint32 terminal_number) :
    Thread(fs_info, filename, Thread::USER_THREAD), fd_(VfsSyscall::open(filename, O_RDONLY)), thread_map_mutex_("thread_map_mutex_")
{
  ProcessRegistry::instance()->processStart(); //should also be called if you fork a process

  if (fd_ >= 0)
    loader_ = new Loader(fd_);

  if (!loader_ || !loader_->loadExecutableAndInitProcess())
  {
    debug(USERPROCESS, "Error: loading %s failed!\n", filename.c_str());
    kill();
    return;
  }


  // UserThread constructor
  // TODO: Set user process ptr
  // TODO: Insert new user thread into user process threads map
  // Initialize kernel and user registers

  // Allocate stack page for new thread
  size_t stack_vaddr = (USER_BREAK / PAGE_SIZE - 1) * PAGE_SIZE;
  while (currentThread->loader_->arch_memory_.checkAddressValid(stack_vaddr)) {
    stack_vaddr -= (PAGE_SIZE * 2);
  }

  size_t page_for_stack = PageManager::instance()->allocPPN();
  currentThread->loader_->arch_memory_.mapPage(stack_vaddr / PAGE_SIZE, page_for_stack, 1);

  // loader_->arch_memory_.mapPage(USER_BREAK / PAGE_SIZE - 1, page_for_stack, 1);


  ArchThreads::createUserRegisters(user_registers_, 0,
                                   (void*) 0,
                                   getStackStartPointer());

  user_registers_->rip = pthread_wrapper_address;
  user_registers_->rsp = (stack_vaddr + PAGE_SIZE - sizeof(pointer));
  user_registers_->rsi = start_routine;
  user_registers_->rdi = arg;

  //ArchThreads::createUserRegisters(user_registers_, loader_->getEntryFunction(),
  //                                 (void*) (USER_BREAK - sizeof(pointer)),
  //                                 getStackStartPointer());

  ArchThreads::setAddressSpace(this, loader_->arch_memory_);
  // sets cr3 register

  debug(USERPROCESS, "ctor: Done loading %s\n", filename.c_str());

  if (main_console->getTerminal(terminal_number))
    setTerminal(main_console->getTerminal(terminal_number));

  switch_to_userspace_ = 1;


  Scheduler::instance()->addNewThread(new_thread);



}

UserProcess::~UserProcess()
{
  assert(Scheduler::instance()->isCurrentlyCleaningUp());
  delete loader_;
  loader_ = 0;

  if (fd_ > 0)
    vfs_syscall.close(fd_);

  delete working_dir_;
  working_dir_ = 0;

  ProcessRegistry::instance()->processExit();
}

void UserProcess::Run()
{
  debug(USERPROCESS, "Run: Fail-safe kernel panic - you probably have forgotten to set switch_to_userspace_ = 1\n");
  assert(false);
}

