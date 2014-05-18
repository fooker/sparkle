import ctrl
import time



if __name__ == '__main__':
  dev = ctrl.Device(1,
                    0x60)
  
  i = 0
  while True:
    for j in xrange(0, len(dev)):
      dev[j].set_hsv(i / 360.0 + j * 1.0 / len(dev),
                     1.0,
                     1.0)
      
    dev.flush()
    
    time.sleep(0.001)
    
    i = (i + 1) % 360
