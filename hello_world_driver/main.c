#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/fs.h> 

/*Static Function Declarations*/
static ssize_t hello_world_read(struct file * file_pointer, char __user * user_space_buffer, size_t count, loff_t *offset);
static ssize_t hello_world_write(struct file * file_pointer, const char __user * user_space_buffer, size_t count, loff_t *offset);

static struct proc_dir_entry *custom_proc_node;
struct proc_ops driver_proc_ops = {.proc_read = hello_world_read, .proc_lseek = default_llseek, .proc_write = hello_world_write};
static char msg[1024] = {0};

static ssize_t hello_world_write(struct file * file_pointer, const char __user * user_space_buffer, size_t count, loff_t *offset) {
	if(count >= sizeof(msg))
		return -EINVAL; // Prevent buffer overflow, Invalid argument

	if(copy_from_user(msg, user_space_buffer, count))
		return -EFAULT; // Bad address
	msg[count] = 0;
	*offset += count;
	printk("Hello World driver written!\n");
	return count;
}

static ssize_t hello_world_read(struct file *file_pointer, char __user *user_space_buffer, size_t count, loff_t *offset) {
	size_t len = strlen(msg);
	
	if (*offset >= len)
		return 0;

	if (copy_to_user(user_space_buffer, msg, len))
		return -EFAULT;

	*offset = len;
	printk("Hello World driver read!\n");
	return len;
}


static int __init helloworld_init(void) {
	printk(KERN_CRIT "Hello World\n");
	custom_proc_node = proc_create("hello_world_driver", 0, NULL, &driver_proc_ops);
	if(custom_proc_node == NULL)
		return -1;
	printk("Done with init!\r\n");
	return 0; //returning a non-zero value indicates an error. 
}

static void __exit helloworld_cleanup(void) {
	proc_remove(custom_proc_node);
	pr_info("Goodbye world\n");
}

module_init(helloworld_init);
module_exit(helloworld_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Viraj Mantri");
MODULE_DESCRIPTION("A simple hello world kernel module");
MODULE_INFO(board, "Beaglebone black REV A5");