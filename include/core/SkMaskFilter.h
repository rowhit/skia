/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkMaskFilter_DEFINED
#define SkMaskFilter_DEFINED

#include "SkBlurTypes.h"
#include "SkCoverageMode.h"
#include "SkFlattenable.h"
#include "SkScalar.h"

class SkMatrix;
struct SkRect;
class SkString;

/** \class SkMaskFilter

    SkMaskFilter is the base class for object that perform transformations on
    the mask before drawing it. An example subclass is Blur.
*/
class SK_API SkMaskFilter : public SkFlattenable {
public:
    /** Create a blur maskfilter.
     *  @param style     The SkBlurStyle to use
     *  @param sigma     Standard deviation of the Gaussian blur to apply. Must be > 0.
     *  @param occluder  The rect for which no pixels need be drawn (b.c. it will be overdrawn
     *                   with some opaque object. This is just a hint which backends are free to
     *                   ignore.
     *  @param respectCTM if true the blur's sigma is modified by the CTM.
     *  @return The new blur maskfilter
     */
    static sk_sp<SkMaskFilter> MakeBlur(SkBlurStyle style, SkScalar sigma, const SkRect& occluder,
                                        bool respectCTM = true);
    static sk_sp<SkMaskFilter> MakeBlur(SkBlurStyle style, SkScalar sigma,
                                        bool respectCTM = true);

    /**
     *  Construct a maskfilter whose effect is to first apply the inner filter and then apply
     *  the outer filter to the result of the inner's. Returns nullptr on failure.
     */
    static sk_sp<SkMaskFilter> MakeCompose(sk_sp<SkMaskFilter> outer, sk_sp<SkMaskFilter> inner);

    /**
     *  Compose two maskfilters together using a coverage mode. Returns nullptr on failure.
     */
    static sk_sp<SkMaskFilter> MakeCombine(sk_sp<SkMaskFilter> filterA, sk_sp<SkMaskFilter> filterB,
                                           SkCoverageMode mode);

    sk_sp<SkMaskFilter> makeWithLocalMatrix(const SkMatrix&) const;

    SK_TO_STRING_PUREVIRT()
    SK_DEFINE_FLATTENABLE_TYPE(SkMaskFilter)

private:
    static void InitializeFlattenables();
    friend class SkFlattenable;
};

#endif
