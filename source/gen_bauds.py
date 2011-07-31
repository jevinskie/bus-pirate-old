#!/usr/bin/env python

import sys

fcy = int(sys.argv[1])
tolerance = float(sys.argv[2])

def find_ubrg(baud, quad_speed):
    global fcy

    if quad_speed:
        divisor = 4
    else:
        divisor = 16

    ubrg = int(float(fcy) / (divisor * baud)) - 1

    ubrg = max(ubrg, 0)
    ubrg = min(ubrg, 2**16-1)

    return ubrg

def find_baud(ubrg, quad_speed):
    global fcy

    if quad_speed:
        divisor = 4
    else:
        divisor = 16

    baud = float(fcy) / (divisor * (ubrg + 1))

    return baud

def find_error(baud, quad_speed):
    desired = baud
    ubrg = find_ubrg(baud, quad_speed)
    actual = find_baud(ubrg, quad_speed)

    error = abs(actual - desired) / desired * 100

    return error

bauds = [300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200,
         230400, 460800, 500000, 576000, 1000000, 1500000, 3000000]

good_bauds = []
good_ubrgs = []
good_quads = []

for baud in bauds:
    ubrg = find_ubrg(baud, False)
    error = find_error(baud, False)
    if error <= tolerance:
        print "%u %u %f" % (baud, ubrg, error)
        good_bauds.append(baud)
        good_ubrgs.append(ubrg)
        good_quads.append(0)
        continue

    ubrg = find_ubrg(baud, True)
    error = find_error(baud, True)
    if error <= tolerance:
        print "%u %u %f 4x" % (baud, ubrg, error)
        good_bauds.append(baud)
        good_ubrgs.append(ubrg)
        good_quads.append(1)
        continue

    print "%u failed" % baud

strlen = 0

strings = open('baud_strings.s', 'w')

strings.write(".global _baud_prompt_msg\n")
strings.write("_baud_prompt_msg:\n")
strings.write('\t.pascii "')
s = 'Set serial port speed: (bps)'
strlen += len(s) + 2
strings.write('%s\\r\\n' % s)

i = 1
for baud in good_bauds:
    s = ' %i. %i' % (i, baud)
    strlen += len(s) + 2
    strings.write('%s\\r\\n' % s)
    i += 1

s = ' %i. BRG raw value' % i
strlen += len(s)
strings.write(s)
strings.write('"\n\n')

strings.close()

header = open('bauds.h', 'w')

header.write('void print_bauds(void);\n\n')
header.write('#define BAUD_MSG_LEN %i\n' % strlen)
header.write('#define NUM_BAUDS %i\n' % len(good_bauds))
header.write('#define DEFAULT_BAUD_INDEX %i\n\n' % good_bauds.index(115200))

header.write("static unsigned int ubrgs[] = {")
header.write(','.join(map(str, good_ubrgs)))
header.write("};\n\n")

header.write("static unsigned char brghs[] = {")
header.write(','.join(map(str, good_quads)))
header.write("};\n\n")

header.close()

