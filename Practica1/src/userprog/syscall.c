#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);
char* get_comando_2(char * cadena){
 int i=0;
  while(cadena[i]!=' '){
  i++;
 }  
 char * comando=malloc(sizeof(char)*i);
 for(int a=0;a<i;a++){
  comando[a]=cadena[a];
 }
 comando[i]='\0';
 return comando;
}

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  uint32_t* esp=f->esp;	
  uint32_t syscall=*esp;
  esp++;
  switch(syscall){
  	case SYS_WRITE:{
  	  int fd=*esp;
  	  esp++;
  	  void* buffer=(void *)*esp;
  	  esp++;
  	  unsigned int size=*esp;
  	  putbuf(buffer,size);
  	  break;	
  	}
  	case SYS_EXIT:{
  		printf("%s: exit(0)\n",get_comando_2(thread_current()->name));
  		thread_exit();
  		break;
  	}
  }	
}