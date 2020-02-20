#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/gpio.h>

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Vladimir Vorobyev <vlad_vorobyev@mail.ru>" );

static struct timer_list my_timer;

static int timer_period = 1000;

static void my_timer_callback(struct timer_list  *timer)
{
    printk(KERN_NOTICE "timer_callback called\n");
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(timer_period));
}

static int __init mygpiomodule_init( void ) {
    int ret;
    printk(KERN_INFO "+> module mygpiomodule start!\n");
    timer_setup( &my_timer, my_timer_callback, 0 );
    ret = mod_timer(&my_timer, jiffies + msecs_to_jiffies(200));
    if (ret)
	    printk(KERN_ALERT "Error in mod_timer\n");
    return 0;
}

static void __exit mygpiomodule_exit( void ) {
	int ret;
	printk(KERN_INFO "+> module mygpiomodule unloaded!\n" );
	ret = del_timer( &my_timer );
	if (ret)
	  printk(KERN_ALERT "The timer is still in use...\n");
}

module_init( mygpiomodule_init );
module_exit( mygpiomodule_exit );

