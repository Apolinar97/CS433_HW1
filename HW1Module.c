/***************************************************
*Written by: Apolinar Camacho
*Instructor: 
Init Date: 1/24/2019 
Due Date: 2/12/2019
File Name: HW1Module.c
Purpose: To learn how to create a kernal module
  and how to load it on the Linux O.S. In addition,
  the other purpose is to learn how to add an 
  entry into the /proc file system.

***************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/param.h>
#include <linux/jiffies.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "hello"
#define MESSAGE "Hello World\n"

//Function prototypes

static ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos); 

static struct file_operations proc_ops = {
  .owner = THIS_MODULE,
  .read = proc_read,

};
//end of function prototypes.

//init function.
int HW1Module_init(void) {
  printk(KERN_INFO "Loading HW1Module into the kernal.\n");
  printk(KERN_INFO "%lu\n", GOLDEN_RATIO_PRIME);
  printk(KERN_INFO "%lu\n", jiffies);
  printk(KERN_INFO "%d\n", HZ);
  
  //Proc part of module
  proc_create(PROC_NAME, 0, NULL, &proc_ops);
  printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
  //end of Proc section.
 
  return 0;
}

//exit function.
void HW1Module_exit(void) {
  printk(KERN_INFO "Removing HW1Module from the kernal.\n");
  printk(KERN_INFO "%lu\n", gcd(3300,24) );
  printk(KERN_INFO "%lu\n", jiffies);

  //start of Proc part of module
  remove_proc_entry(PROC_NAME,NULL);
  printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);

}
//end of preliminary module enter and exit points.
//start of proc_read function
static ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
  int rv = 0;
  char buffer[BUFFER_SIZE];
  static int completed = 0;
  
  if(completed) {
    completed = 0;
    return 0;  

  }
  completed = 1;
  rv = sprintf(buffer, "Hello world\n");
  copy_to_user(usr_buf, buffer,rv);
  return rv;
  
}



//end of proc_read function


//Macros for entry and exit points.
module_init(HW1Module_init);
module_exit(HW1Module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module for Assignment 1 for CS433");
MODULE_AUTHOR("Apolinar Camacho");
