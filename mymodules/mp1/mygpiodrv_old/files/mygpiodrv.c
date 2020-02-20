#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/gpio.h>

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Vladimir Vorobyev <vlad_vorobyev@mail.ru>" );

static struct timer_list my_timer;

static int gpio_pin = 14;
static int gpio_value = 1;
static int timer_period = 100;
//module_param(gpio_pin, int, 0755);

static struct gpio led;


static void my_timer_callback(struct timer_list  *timer)
{
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(timer_period));
    printk(KERN_NOTICE "timer_callback called\n");
    gpio_value = (gpio_value) ? 0 : 1;
    gpio_set_value(gpio_pin, gpio_value);
}

static int __init mygpiomodule_init( void ) {
    int ret;
    printk(KERN_INFO "+> module mygpiomodule start!\n");
	led.gpio = gpio_pin;
	led.flags = GPIOF_OUT_INIT_LOW;
	led.label = "LED";
	printk(KERN_INFO " GPIO number %d\n", gpio_pin);
	if (!gpio_is_valid(gpio_pin))
	{
	  printk(KERN_ALERT " GPIO number %d not valid.\n", gpio_pin);
	  return -1;
	}
	ret = gpio_request(gpio_pin,"LED");
	if (ret)
	{
	  printk(KERN_ALERT "Gpio request failed.\n");
	  return -2;
	}
	gpio_direction_output(gpio_pin, 0);
	gpio_set_value(gpio_pin, gpio_value);
	timer_setup( &my_timer, my_timer_callback, 0 );
	ret = mod_timer(&my_timer, jiffies + msecs_to_jiffies(200));
	if (ret)
		printk(KERN_ALERT "Error in mod_timer\n");
	return 0;
}

static void __exit mygpiomodule_exit( void ) {
	int ret;
	printk(KERN_INFO "+> module mygpiomodule unloaded!\n" );
	gpio_free(led.gpio);
	ret = del_timer( &my_timer );
	if (ret)
	  printk(KERN_ALERT "The timer is still in use...\n");
}

module_init( mygpiomodule_init );
module_exit( mygpiomodule_exit );

