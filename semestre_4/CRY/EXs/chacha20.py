import base64

m = "You will have trouble finding the flag. The original ChaCha20 is"
c = "0C1dXd6CI4K9Wr55upsJKGWUgtvLWaLTTp3fidbnm6vN8M299QHhhJzXGpyz+MtUFnA7zDb2HPH2DgIa8QuGgvoTB/Lmvc3QESI9jGfuO1p3lhkE3LAv5EKkAj7tbrPI2kd06CPCgg=="


#Computes the Chacha20 initial state with given key, position and nonce
def initialState(key, pos, nonce):
    return [0x61707865, 0x3320646e,
      0x79622d32, 0x6b206574] + key + pos + nonce

#Cyclic shift left
def roll(x, n):
    return (x << n) % (2 << 31) + (x >> (32-n))

def quarter_round(a, b, c, d):
    a = (a+b) %(1<<32)
    d = roll(d^a, 16)
    c = (c+d)%(1<<32)
    b = roll(b^c, 12)
    a = (a+b)%(1<<32)
    d = roll(d^a,  8)
    c = (c+d)%(1<<32)
    b = roll(b^c,  7)
    return a, b, c, d

#Double round on a Chacha20 state seen as a 16 32-bit integer array
def double_round(state):
    state[0],state[4],state[8],state[12] = quarter_round(state[0],state[4],state[8],state[12])
    state[1],state[5],state[9],state[13] = quarter_round(state[1],state[5],state[9],state[13])
    state[2],state[6],state[10],state[14] = quarter_round(state[2],state[6],state[10],state[14])
    state[3],state[7],state[11],state[15] = quarter_round(state[3],state[7],state[11],state[15])
    state[0],state[5],state[10],state[15] = quarter_round(state[0],state[5],state[10],state[15])
    state[1],state[6],state[11],state[12] = quarter_round(state[1],state[6],state[11],state[12])
    state[2],state[7],state[8],state[13] = quarter_round(state[2],state[7],state[8],state[13])
    state[3],state[4],state[9],state[14] = quarter_round(state[3],state[4],state[9],state[14])

def chacha(state):
    for _ in range(10):
        double_round(state)
    return state

#Converts a 32-bit word into 4 bytes
def w2b(word):
    return [(word & 0x000000ff), ((word & 0x0000ff00) >> 8),
            ((word & 0x00ff0000) >> 16), ((word & 0xff000000) >> 24)]

#Converts four bytes into a 32-bit word
def _b2w(bytes):
    return (bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24)) & 0xffffffff
        
#Converts a 64 byte array into a Chacha state
def streamToState(stream):
    res = []
    for i in range(16):
        res.append(_b2w(stream[i*4 :(i+1)*4]))
    return res

#Converts a chacha state into a bitstring for final xoring operation
def from_little_endian(state):
    res = []
    for i in state:
        res = res + w2b(i)
    return res

#Final xoring operation: plaitext XOR bit stream
def finalXor(pt_array, state):
    stream = from_little_endian(state)
    ciphertext = []
    for i in range(64):
        ciphertext.append(stream[i]^pt_array[i]) 
    return bytes(ciphertext)

def chacha_encrypt(plaintext, key, pos, nonce):
    if len(plaintext) != 64:
        print("plaintext needs to be 512 bits not " +str(len(plaintext)))
        return
    pt_array = bytearray(plaintext, "utf8")
    return finalXor(pt_array, chacha(initialState(key, pos, nonce)))
