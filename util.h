//
// Created by Spencer Martin on 8/11/21.
//

#ifndef GBAEMU_UTIL_H
#define GBAEMU_UTIL_H

#endif //GBAEMU_UTIL_H

template <int bits>
inline uint32_t sign_extend(uint32_t x) {
    constexpr uint32_t m = 1u << (bits - 1);
    return (x ^ m) - m;
}