from Crypto.Cipher import AES
from Crypto.Util.strxor import strxor

rate = 15
cipher = AES.new(b"\x07"*16, AES.MODE_ECB)
def permutation(b):
    return cipher.encrypt(b)

def pad(message, rate):
    missing = rate - len(message)% rate
    if missing == 0: 
        missing = rate
    message += b"\x80" + b"\x00"*(missing - 1)
    return message 

#Hashes the message to a specific output_size
def sponge(rate, message, output_size):
    #padding
    message = pad(message, rate)
    
    blocks = [message[rate*i:rate*(i+1)] for i in range(len(message)//rate)]
    state = b"\x00"*16
    #absorbing
    for b in blocks:
        state = strxor(state[:rate], b) + state[rate:]
        state = permutation(state)
    #squeezing
    hash  = b""
    while len(hash) < output_size:
        hash += state[:rate]
        state = permutation(state)
    return hash[:output_size]
