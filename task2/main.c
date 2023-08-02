#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eitan");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

//A function is invoked when the module is activated
static int __init lkm_example_init(void) {
    printk(KERN_INFO "Hello, Check Point!\n");
    return 0;
}

//A function is invoked when the module is deleted
static void __exit lkm_example_exit(void) {
    printk(KERN_INFO "Goodbye, Check Point!\n");
}

//Running functions sent as a parameter when creating/deleting the module
module_init(lkm_example_init);
module_exit(lkm_example_exit);