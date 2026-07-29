#pragma once

namespace pinmap {
    constexpr uint8_t enc_1     = 2;
    constexpr uint8_t enc_2     = 3;
    constexpr uint8_t gate      = 9;
    constexpr uint8_t dac_cs    = 10;
    // 11, 12, 13 used by spi
    namespace buttons {
        constexpr uint8_t in1   = A0;
        constexpr uint8_t outA  = 5;
        constexpr uint8_t outB  = 6;
        constexpr uint8_t shift = 7;
        constexpr uint8_t alt   = 8;
        constexpr uint8_t enc_bt    = 4;
    }
}