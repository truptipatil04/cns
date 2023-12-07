MODE_ECB = 1
MODE_CBC = 2
MODE_CFB = 3
MODE_PGP = 4  # optional
MODE_OFB = 5
MODE_CTR = 6


class BlockCipher:
    
    def encrypt_block(self, block: bytes) -> bytes:
        
        raise NotImplementedError
    
    def decrypt_block(self, block: bytes) -> bytes:
        
        raise NotImplementedError


class Counter:
    
    def __init__(self, nonce: bytes, block_size: int, byte_order='big'):
        
        self.nonce = nonce
        self.counter_size = block_size - len(nonce)
        self.byte_order = byte_order
        self.counter = 0
    
    def __call__(self) -> bytes:
        
        out = self.nonce + self.counter.to_bytes(
            self.counter_size, self.byte_order
        )
        self.counter += 1
        return out


class BlockCipherWrapper:
    
    def __init__(self):
        """initiate instance attributes."""
        # PEP 272 required attributes
        self.block_size: int = NotImplemented  # measured in bytes
        self.IV: bytes = NotImplemented  # initialization vector
        # other attributes
        self.mode: int = NotImplemented
        self.cipher: BlockCipher = NotImplemented
        self.counter: Counter = NotImplemented
        self.segment_size: int = NotImplemented
    
    def encrypt(self, byte_string: bytes) -> bytes:
        
        if self.mode == MODE_CFB and len(byte_string) * 8 % self.segment_size:
            raise ValueError("Message length doesn't match segment size")
        if self.mode == MODE_CFB and self.segment_size & 7:
            raise NotImplementedError
        if self.mode != MODE_CFB and len(byte_string) % self.block_size:
            raise ValueError("Message length doesn't match block size")
        
        blocks = [
            byte_string[i:i+self.block_size]
            for i in range(0, len(byte_string), self.block_size)
        ]
        
        if self.mode == MODE_ECB:
            return b''.join([
                self.cipher.encrypt_block(block) for block in blocks
            ])
        elif self.mode == MODE_CBC:
            cipher_blocks = [self.IV]
            for block in blocks:
                cipher_blocks.append(
                    self.cipher.encrypt_block(
                        self.xor(block, cipher_blocks[-1])
                    )
                )
            return b''.join(cipher_blocks[1:])
        elif self.mode == MODE_CFB:
            s = self.segment_size >> 3
            cipher = b''
            current_input = self.IV
            while byte_string:
                cipher += self.xor(
                    byte_string[:s],
                    self.cipher.encrypt_block(current_input)[:s]
                )
                byte_string = byte_string[s:]
                current_input = current_input[s:] + cipher[-s:]
            return cipher
        elif self.mode == MODE_PGP:
            raise NotImplementedError
        elif self.mode == MODE_OFB:
            last_output = self.IV
            cipher_blocks = [self.IV]
            for block in blocks:
                last_output = self.cipher.encrypt_block(last_output)
                cipher_blocks.append(self.xor(block, last_output))
            return b''.join(cipher_blocks[1:])
        elif self.mode == MODE_CTR:
            cipher_blocks = []
            for block in blocks:
                ctr = self.counter()
                if len(ctr) != self.block_size:
                    raise ValueError("Counter has the wrong size")
                cipher_blocks.append(
                    self.xor(self.cipher.encrypt_block(ctr), block)
                )
            return b''.join(cipher_blocks)
        else:
            raise NotImplementedError("This mode is not supported")
    
    def decrypt(self, byte_string: bytes) -> bytes:
        
        if self.mode == MODE_CFB and len(byte_string) * 8 % self.segment_size:
            raise ValueError("Message length doesn't match segment size")
        if self.mode == MODE_CFB and self.segment_size & 7:
            raise NotImplementedError
        if self.mode != MODE_CFB and len(byte_string) % self.block_size:
            raise ValueError("Message length doesn't match block size")
        
        # split up into blocks
        blocks = [
            byte_string[i:i+self.block_size]
            for i in range(0, len(byte_string), self.block_size)
        ]
        
        if self.mode == MODE_ECB:
            return b''.join([
                self.cipher.decrypt_block(block)
                for block in blocks
            ])
        elif self.mode == MODE_CBC:
            plain_blocks = []
            blocks.insert(0, self.IV)
            for i in range(1, len(blocks)):
                plain_blocks.append(self.xor(
                    self.cipher.decrypt_block(blocks[i]), blocks[i-1]
                ))
            return b''.join(plain_blocks)
        elif self.mode == MODE_CFB:
            s = self.segment_size >> 3
            plain = b''
            current_input = self.IV
            while byte_string:
                plain += self.xor(
                    byte_string[:s],
                    self.cipher.encrypt_block(current_input)[:s]
                )
                current_input = current_input[s:] + byte_string[:s]
                byte_string = byte_string[s:]
            return plain
        elif self.mode == MODE_PGP:
            raise NotImplementedError("PGP mode is not supported")
        elif self.mode == MODE_OFB:
            return self.encrypt(byte_string)
        elif self.mode == MODE_CTR:
            return self.encrypt(byte_string)
        else:
            raise ValueError("Unknown mode")
    
    def xor(self, block1, block2):

        size = (
            self.segment_size >> 3
            if self.mode == MODE_CFB
            else self.block_size
        )
        if not (len(block1) == len(block2) == size):
            raise ValueError(str(size))
        return bytes([block1[i] ^ block2[i] for i in range(size)])