// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "platform/graphics/paint/FloatClipDisplayItem.h"

#include "platform/graphics/GraphicsContext.h"
#include "public/platform/WebDisplayItemList.h"
#include "third_party/skia/include/core/SkScalar.h"

namespace blink {

void FloatClipDisplayItem::replay(GraphicsContext& context) const
{
    context.save();
    context.clip(m_clipRect);
}

void FloatClipDisplayItem::appendToWebDisplayItemList(const IntRect& visualRect, WebDisplayItemList* list) const
{
    list->appendFloatClipItem(visualRect, m_clipRect);
}

void EndFloatClipDisplayItem::replay(GraphicsContext& context) const
{
    context.restore();
}

void EndFloatClipDisplayItem::appendToWebDisplayItemList(const IntRect& visualRect, WebDisplayItemList* list) const
{
    list->appendEndFloatClipItem(visualRect);
}

#ifndef NDEBUG
void FloatClipDisplayItem::dumpPropertiesAsDebugString(WTF::StringBuilder& stringBuilder) const
{
    DisplayItem::dumpPropertiesAsDebugString(stringBuilder);
    stringBuilder.append(WTF::String::format(", floatClipRect: [%f,%f,%f,%f]}",
        m_clipRect.x(), m_clipRect.y(), m_clipRect.width(), m_clipRect.height()));
}

#endif

} // namespace blink
