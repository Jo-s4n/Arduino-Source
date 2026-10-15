/*  Scratch CI probe (do not merge)
 *
 *  Does Apple Clang's arm_neon.h provide any 128-bit-table TBL
 *  intrinsic? The only TBL family confirmed present on Xcode 16.4 /
 *  clang 17 is the 64-bit one (vtbl1_u8 / vtbl2_u8): vtbl2q_u8 failed
 *  with "use of undeclared identifier" on the first #1587 Mac run, and
 *  the vtbl1q_u8-based gather commit (f35466145) also failed to compile
 *  on Mac. This probe settles it: if Mac CI compiles this file,
 *  vtbl1q_u8 exists and the NEON kernel's Clang path can switch to a
 *  single 128-bit TBL for up.
 *
 */

#ifdef PA_AutoDispatch_arm64_20_M1

#include <arm_neon.h>

namespace PokemonAutomation{
namespace Kernels{
namespace AudioResampler{

float32x4_t pa_neon_tbl1q_probe(uint8x16_t tab, uint8x16_t idx)
{
    return vreinterpretq_f32_u8(vtbl1q_u8(idx, tab));
}

}
}
}
#endif
