import smbus
import colorsys



class Dot(object):
  def __init__(self,
               device,
               index):
    self.__device = device
    self.__index = index
    
  
  def set_rgb(self, r, g, b):
    self.__device[self.__index] = (r, g, b)
    
  
  def set_hsv(self, r, g, b):
    self.__device[self.__index] = colorsys.hsv_to_rgb(r, g, b)



class Device(object):
  def __init__(self,
               bus,
               addr,
               size = 24,
               max_value = 0x3F):
    self.__bus = smbus.SMBus(bus)
    
    self.__addr = addr
    
    self.__size = size
    self.__max_value = max_value
    
    self.__data = [int(0x00),
                   int(0x00),
                   int(0x00)] * size
  
  
  def __len__(self):
    return self.__size
    
  
  def __getitem__(self, index):
    return Dot(device = self,
               index = index)
    
  
  def __setitem__(self, index, values):
    self.__data[index * 3 + 0] = int(max(0.0, min(values[0], 1.0)) * self.__max_value)
    self.__data[index * 3 + 1] = int(max(0.0, min(values[1], 1.0)) * self.__max_value)
    self.__data[index * 3 + 2] = int(max(0.0, min(values[2], 1.0)) * self.__max_value)
  
  
  def flush(self):
    for i in xrange(0, self.__size):
      self.__bus.write_i2c_block_data(self.__addr, i, [self.__data[i * 3 + 0],
                                                       self.__data[i * 3 + 1],
                                                       self.__data[i * 3 + 2]])
