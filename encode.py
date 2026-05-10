import struct

s = 640*400
frames = open("frames.raw", "rb").read()
out = open("badapple", "wb")

i = 1
prev = 1 if frames[0] == 255 else 0

for f in range(1, len(frames)):
    if f % s == 0 and i != 0:
        out.write(struct.pack('I', i))
        out.write(struct.pack('B', prev))
        out.write(struct.pack('B', 255))

        i = 1
        prev = 1 if frames[f] == 255 else 0
        continue

    p = 1 if frames[f] == 255 else 0

    if p == prev:
        i += 1
    else:
        out.write(struct.pack('I', i))
        out.write(struct.pack('B', prev))
        out.write(struct.pack('B', 0))
        prev = p
        i = 1
out.write(struct.pack('I', i))
out.write(struct.pack('B', prev))
out.write(struct.pack('B', 255))
