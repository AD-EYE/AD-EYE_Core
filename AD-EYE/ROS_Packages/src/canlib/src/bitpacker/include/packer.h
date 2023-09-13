/*-----------------------------------------------------------------------------

BSD 3-Clause License

Copyright (c) 2023, Konstantin Tyurin, kt@pluraf.se

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

-----------------------------------------------------------------------------*/

#include <cstdint>
#include <vector>

class Packer {
public:
    static void pack(std::vector<uint8_t>& data, unsigned int start_bit, unsigned int length, uint64_t val) {
        if (sizeof(val) * 8 < length) {
            throw;
        }
        int start_byte = start_bit / 8;
        int first_bit_offset = start_bit % 8;
        val &= ~static_cast<uint64_t>(0) >> (64 - length);
        uint8_t b = data[start_byte];
        int bits_in_byte = 8 - first_bit_offset;
        uint8_t mask = 0xFF >> bits_in_byte;
        if (bits_in_byte > length) {
            mask |= ~(0xFF >> (bits_in_byte - length));
        }
        b &= mask;
        b |= static_cast<uint8_t>(val << first_bit_offset);
        data[start_byte] = b;
        val >>= 8 - first_bit_offset;
        int rix = 1;
        for (; rix < length / 8; rix++) {
            data[start_byte + rix] = static_cast<uint8_t>(val);
            val >>= 8;
        }

        int last_bits = length - (rix * 8 - first_bit_offset);
        if (last_bits > 0) {
            uint8_t b = data[start_byte + rix];
            b &= 0xFF << last_bits;
            b |= static_cast<uint8_t>(val);
            data[start_byte + rix] = b;
        }
    }

    static uint64_t unpack(std::vector<uint8_t>& data, unsigned int start_bit, unsigned int length) {
        uint64_t val = 0;
        int start_byte = start_bit / 8;
        int first_bit_offset = start_bit % 8;
        int rix = 0;
        int bits_copied = 0;
        if (first_bit_offset != 0) {
            val = data[start_byte] >> first_bit_offset;
            bits_copied = 8 - first_bit_offset;
            rix++;
        }
        for (; rix < length / 8; rix++) {
            uint64_t t = data[start_byte + rix];
            val |= t << bits_copied;
            bits_copied += 8;
        }

        if (bits_copied < length) {
            uint64_t t = data[start_byte + rix] & ~(0xFF << (length - bits_copied));
            val |= t << bits_copied;
        }

        val &= ~static_cast<uint64_t>(0) >> (64 - length);

        return val;
    }
};
