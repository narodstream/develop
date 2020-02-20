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
static int timer_period = 200;
//module_param(gpio_pin, int, 0755);

//static struct gpio led;
/*
struct gpio {
	unsigned	gpio;
	unsigned long	flags;
	const char	*label;
};
*/

static struct gpio leds_gpios[] = {
	{ 80, GPIOF_OUT_INIT_LOW, "PORTF0" },
	{ 81, GPIOF_OUT_INIT_LOW, "PORTF1" }
};


static void my_timer_callback(struct timer_list  *timer)
{
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(timer_period));
    printk(KERN_NOTICE "timer_callback called\n");
    gpio_value = (gpio_value) ? 0 : 1;
    gpio_set_value(leds_gpios[0].gpio, (gpio_value) ? 0 : 1);
    gpio_set_value(leds_gpios[1].gpio, (gpio_value) ? 1 : 0);
}

static int __init mygpiomodule_init( void ) {
    int ret;
    printk(KERN_INFO "+> module mygpiomodule start!\n");
	if ((!gpio_is_valid(80)) && (!gpio_is_valid(81)))
	{
	  printk(KERN_ALERT " GPIO numbers not valid.\n", gpio_pin);
	  return -1;
	}
	ret = gpio_request_array(leds_gpios, ARRAY_SIZE(leds_gpios));
	if (ret)
	{
	  printk(KERN_ALERT "Gpio request failed.\n");
	  return -2;
	}
	gpio_direction_output(leds_gpios[0].gpio, 0);
	gpio_direction_output(leds_gpios[1].gpio, 0);
	gpio_set_value(leds_gpios[0].gpio, gpio_value);
	gpio_set_value(leds_gpios[1].gpio, gpio_value);
	timer_setup( &my_timer, my_timer_callback, 0 );
	ret = mod_timer(&my_timer, jiffies + msecs_to_jiffies(200));
	if (ret)
		printk(KERN_ALERT "Error in mod_timer\n");
	return 0;
}

static void __exit mygpiomodule_exit( void ) {
	int ret;
	printk(KERN_INFO "+> module mygpiomodule unloaded!\n" );
	gpio_free_array(leds_gpios, ARRAY_SIZE(leds_gpios));
	ret = del_timer( &my_timer );
	if (ret)
	  printk(KERN_ALERT "The timer is still in use...\n");
}

module_init( mygpiomodule_init );
module_exit( mygpiomodule_exit );

