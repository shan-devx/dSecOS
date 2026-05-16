import struct

s = 640*400
frames = open("frames.raw", "rb").read()
out = open("badapple", "wb")

for i in range(0, len(frames), 8):
    b = 0
    for px in frames[i:i+8]:
        a = 1 if px == 255 else 0
        b = (b << 1) | a
        
    out.write(struct.pack('B', b))
print("done!")
