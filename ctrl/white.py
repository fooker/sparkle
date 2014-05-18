import ctrl
import time
import random




if __name__ == '__main__':
  dev = ctrl.Device(bus = 1,
                    addr = 0x60)
  
  while True:
    blackout = random.randint(0, len(dev) - 1)
    
    for i in xrange(len(dev)):
      if i == blackout:
        dev[i].set_rgb(0.0, 0.0, 0.0)
      else:
        dev[i].set_rgb(1.0, 1.0, 1.0)
    
    dev.flush()
      
    time.sleep(1.0)
    

