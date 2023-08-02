#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("benny");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

// Declare a variable to hold the string parameter
static char* my_string = "World";

// Register the module parameter
module_param(my_string, charp, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(my_string, "A string that will be stored in the kernel module");

//A function is invoked when the module is activated
static int __init lkm_example_init(void) {
    printk(KERN_INFO "Hello, %s!\n", my_string);
    return 0;
}

//A function is invoked when the module is deleted
static void __exit lkm_example_exit(void) {
    printk(KERN_INFO "Goodbye, %s!\n", my_string);;
}

//Running functions sent as a parameter when creating/deleting the module
module_init(lkm_example_init);
module_exit(lkm_example_exit);