"""
An interface to the external motor controller in the LL turing machine
This matches motor_controller_iface.c

Author: Ben Nahill <bnahill@gmail.com>
"""

import serial
import struct
from exception import Exception



class MotorController:    
    """ An interface to the external motor controllers that drive the turing
    machine
    
    Serial command format:
    0    1    2         3         len+1
    len  cmd  payload_0 payload_1 payload_len
    
    Response format:
    0    1    2         3         len+1
    len  stat payload_0 payload_1 payload_len
    
    - len is the payload length
    - minimum command is [0 cmd]
    - minimum response is [0 stat]
    - maximum payload is 254B, 255 is reserved

    """
    CMD_INIT        = 1
    CMD_STAT        = 2
    CMD_MOVE_LEFT   = 3
    CMD_MOVE_RIGHT  = 4
    CMD_WRITE_ONE   = 5
    CMD_WRITE_TWO   = 6
    CMD_ERASE       = 7

    STAT_OKAY       = 1
    STAT_ERR_PARAM  = 2
    STAT_ERR_RUN    = 3

    def __init__(self, port, baud, timeout=2.0):
        assert baud in serial.BAUDRATES, "Unsupported baud rate"
        self.port = port
        self.baud = baud
        self.timeout = timeout
        self.s = serial.Serial(port=port, baudrate=baud, timeout=timeout)
        
    def read_response(self):
        try:
            r = struct.unpack("B", self.s.read(size=1))[0]
        except:
            raise Exception("Didn't get a response!")
        assert r != 0, "Got a return length of zero...."
        r = self.s.read(size=r)
        stat = struct.unpack("B", r[0])
        payload = r[1:]
        return (stat, payload)
    
    def cmd_stat(self):
        payload = struct.pack("BB", 0, self.CMD_INIT)
        self.s.flushInput()
        self.s.write(payload)
        stat, _ = self.read_response()
        return stat
    
    def cmd_init(self):
        payload = struct.pack("BB", 0, self.CMD_INIT)
        self.s.flushInput()
        self.s.write(payload)
        stat, _ = self.read_response()
        return stat
    
    def cmd_move_right(self, callback=None):
        pass
    
    def cmd_move_right(self, callback=None):
        pass
    
