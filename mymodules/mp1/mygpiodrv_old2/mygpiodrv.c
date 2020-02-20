#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/gpio.h>

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Vladimir Vorobyev <vlad_vorobyev@mail.ru>" );

static int gpio_pin = 14;
//module_param(gpio_pin, int, 0755);

static struct gpio led;

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
      gpio_set_value(gpio_pin, 1);

   return 0;
}

static void __exit mygpiomodule_exit( void ) {
   gpio_free(led.gpio);
   printk(KERN_INFO "+> module mygpiomodule unloaded!\n" );
}

module_init( mygpiomodule_init );
module_exit( mygpiomodule_exit );

