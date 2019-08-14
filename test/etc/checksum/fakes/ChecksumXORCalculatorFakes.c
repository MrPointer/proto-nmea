//
// Created by Timor Gruber on 15/08/2019.
// Copyright (c) 2019 Takpit. All rights reserved.
//

#include "ChecksumXORCalculatorFakes.h"

DEFINE_FAKE_VALUE_FUNC(uint32_t, calculateRangeChecksum, const unsigned char *, const unsigned char *)

DEFINE_FAKE_VALUE_FUNC(uint32_t, calculateLengthChecksum, const unsigned char *, size_t)

DEFINE_FAKE_VALUE_FUNC(uint32_t, calculateChecksum, const unsigned char *)
