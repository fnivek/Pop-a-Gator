from bluetooth import *
import sys
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

gamepad_map = {
    'LEFT_STICK_LR'         : 2,
    'LEFT_STICK_UD'         : 3,
    'RIGHT_STICK_LR'        : 4,
    'RIGHT_STICK_UD'        : 5,
    'LEFT_TRIGGER'          : 6,
    'RIGHT_TRIGGER'         : 7,
    'ABXY_BUMPERS'          : 8,
    'SELECT_START_STICKS_?' : 9,        # The left and the right triggers if depresed far enough will set a bit
    'DPAD'                  : 10
}

button_bitmask = {
    'ABXY_BUMPERS'          : [('A', 0x1), ('B', 0x2), ('X', 0x8), ('Y', 0x10), ('LEFT_BUMPER', 0x40), ('RIGHT_BUMPER', 0x80)],
    'SELECT_START_STICKS_?' : [('SELECT', 0x4), ('START', 0x8), ('LEFT_STICK', 0x20), ('RIGHT_STICK', 0x40), ('LEFT_TRIGGER', 0x1), ('RIGHT_TRIGGER', 0x2)]
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

try:
    while True:
        data = sock.recv(1024)
        print '-----------------'
        formated_data = [ord(c) for c in data]
        if len(formated_data) < 10:
            print 'Home button'
            continue

        for name, position in gamepad_map.iteritems():
            output = name + " : " + str(formated_data[position])
            if name in button_bitmask.keys():
                for mask in button_bitmask[name]:
                    output += "\n\t" + mask[0] + ": " + ('1' if (mask[1] & formated_data[position]) else '0')
            elif name == "DPAD":
                output += "\n\tDirection: " + dpad_map[formated_data[position]]

            print output

finally:
    sock.close()