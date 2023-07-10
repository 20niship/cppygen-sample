#pragma once

namespace Shell
{
struct Piyoyo {
    int value;
    int getValue() { return value; }
    void setValue(int val) { value = val; }
    static Piyoyo StaticFunc(){ return Piyoyo(); }
};
}  // namespace Shell
