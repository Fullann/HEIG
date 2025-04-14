from Crypto.Cipher import AES
from Crypto.Util.strxor import strxor
import itertools
import base64
import sys

# Configuration initiale
rate = 15
cipher = AES.new(b"\x07"*16, AES.MODE_ECB)
target_hash = base64.b64decode('zZFA10Jx7vH5g/liWgyzWfXCuiM7GOEEUtFNeeN64xq9Pa6SbjY9+nAbuE2JCjl7y69uO4zHRZTYmT2Yi925Ag==')

def pad(message, rate):
    missing = rate - len(message) % rate
    return message + b"\x80" + b"\x00"*(missing - 1) if missing != 0 else message

def custom_sponge(message):
    message = pad(message, rate)
    blocks = [message[i*rate:(i+1)*rate] for i in range(len(message)//rate)]
    state = b"\x00"*16
    for b in blocks:
        state = strxor(state[:rate], b) + state[rate:]
        state = cipher.encrypt(state)
    return state[:rate]

def crack_flag():
    charset = [bytes([i]) for i in range(0x20, 0x7f)]  # ASCII imprimable
    prefix = b'FLAG{'
    suffix_padding = b'}\x80' + b'\x00'*10

    for c1, c2, c3 in itertools.product(charset, repeat=3):
        block2 = c1 + c2 + c3 + suffix_padding[:12]  # 3 chars + 12 bytes fixes
        
        for capacity in range(256):
            s2_candidate = target_hash[:15] + bytes([capacity])
            try:
                T = cipher.decrypt(s2_candidate)
            except:
                continue
            
            s1_xor = strxor(T[:15], block2)
            s1_candidate = s1_xor + bytes([T[15]])
            
            try:
                block1_padded = cipher.decrypt(s1_candidate)
            except:
                continue

            if block1_padded[15:] != b'\x00':
                continue
            
            if block1_padded.startswith(prefix):
                part1 = block1_padded[5:15].decode('ascii', errors='ignore')
                part2 = (c1 + c2 + c3).decode('ascii', errors='ignore')
                candidate = f"FLAG{{{part1}{part2}}}"
                
                if len(candidate) == 19:
                    try:
                        if custom_sponge(candidate.encode()) == target_hash[:15]:
                            print(f"\n[SUCCESS] Flag found: {candidate}")
                            return
                    except:
                        continue

        sys.stdout.write(f"\rTesting: {c1+c2+c3}"), sys.stdout.flush()

if __name__ == "__main__":
    print("Starting brute force attack...")
    crack_flag()
