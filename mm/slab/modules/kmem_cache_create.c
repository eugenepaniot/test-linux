/**
 *	File	./kmem_cache_create.c
 *	Time	2021.11.05
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/gfp.h>

struct test_struct {
	int id;
	int ip;
	char *name;
};

#define SLAB_NAME	"rtoax"
#define SLAB_ELEM	32
static struct kmem_cache *test_slab;

void test_constructor(void *data)
{
	static int count = 0;
	struct test_struct *test = (struct test_struct*)data;
	test->id = 1;
	count++;
	pr_info("Ctor test_struct. %d\n", count);
}

static int create_slab(void)
{
	test_slab = kmem_cache_create(SLAB_NAME, 
							sizeof(struct test_struct),
							0, 
							SLAB_PANIC, 
							test_constructor);
	if(!test_slab) {
		pr_err("Create slab fail.\n");
		return -1;
	}
	return 0;
}

static void test__slab(void)
{
	int i;
	char *datas[SLAB_ELEM] = {NULL};

	if(!test_slab) {
		pr_warn("not test.\n");
		return;
	}

	for(i=0; i<SLAB_ELEM; i++) {
		datas[i] = kmem_cache_alloc(test_slab, GFP_KERNEL);	
	}
	for(i=0; i<SLAB_ELEM; i++) {
		kmem_cache_free(test_slab, datas[i]);
		datas[i] = NULL;
	}
	return;
}

static void destroy_slab(void)
{
	if(test_slab) {
		kmem_cache_destroy(test_slab);
	}
}

static int kernel_init(void)
{
    printk(KERN_INFO "my init.\n");
	create_slab();
	test__slab();
    return 0;
}

static void kernel_exit(void)
{
	destroy_slab();
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
