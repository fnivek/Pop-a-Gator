#!/usr/bin/env python

from bluetooth import *
import sys
from collections import OrderedDict

services = find_service()

gamepad = None

for svc in services:
    if svc['name'] == 'SPP Channel':
        gamepad = svc

if gamepad is None:
    print "Failed to find gamepad"
    sys.exit(0)

protocol = gamepad['protocol']
if protocol == 'RFCOMM':
    protocol = RFCOMM
elif protocol == 'L2CAP':
    protocol = L2CAP
else:
    print "Unkown service!"
    sys.exit(0)

sock=BluetoothSocket( protocol )
sock.connect((gamepad['host'], int(gamepad['port'])))

print 'Connected'

gamepad_map = OrderedDict()
gamepad_map['LEFT_STICK_LR'] =         2
gamepad_map['LEFT_STICK_UD'] =         3
gamepad_map['RIGHT_STICK_LR'] =        4
gamepad_map['RIGHT_STICK_UD'] =        5
gamepad_map['LEFT_TRIGGER'] =          6
gamepad_map['RIGHT_TRIGGER'] =         7
gamepad_map['ABXY_BUMPERS'] =          8
gamepad_map['SELECT_START_STICKS_?'] = 9        # The left and the right triggers if depresed far enough will set a bit
gamepad_map['DPAD'] =                  10

button_bitmask = {
    'ABXY_BUMPERS'          : [('A', 0x1), ('B', 0x2), ('X', 0x8), ('Y', 0x10), ('LEFT_BUMPER', 0x40), ('RIGHT_BUMPER', 0x80)],
    'SELECT_START_STICKS_?' : [('SELECT', 0x4), ('START', 0x8), ('LEFT_STICK', 0x20), ('RIGHT_STICK', 0x40) ]#('LEFT_TRIGGER', 0x1), ('RIGHT_TRIGGER', 0x2)]
}

dpad_map = {
    0 : 'NOT_PRESSED',
    1 : 'UP',
    2 : 'UP_RIGHT',
    3 : 'RIGHT',
    4 : 'DOWN_RIGHT',
    5 : 'DOWN',
    6 : 'DOWN_LEFT',
    7 : 'LEFT',
    8 : 'UP_LEFT',
}

raw_data = ''
state = ''
try:
    while True:
        data = sock.recv(1024)
        print '-----------------'
        formated_data = [ord(c) for c in data]
        print formated_data
        for d in formated_data:
            raw_data += str(d)
            raw_data += ', '

        if len(formated_data) < 10:
            print 'Home button'
            continue

        state += '{0, '
        for name, position in gamepad_map.iteritems():
            output = name + " : " + str(formated_data[position])
            if name in button_bitmask.keys():
                for mask in button_bitmask[name]:
                    value = mask[1] & formated_data[position]
                    state += str(value)
                    state += ', '
                    output += "\n\t" + mask[0] + ": " + ('1' if (value) else '0')
            elif name == "DPAD":
                state += str(formated_data[position] & 0xF)
                output += "\n\tDirection: " + dpad_map[formated_data[position]]
                state += ', '
            else:
                state += str(formated_data[position])
                state += ', '

            print output

        state += '},\n'

finally:
    print raw_data
    print '\n'
    print state
    sock.close()