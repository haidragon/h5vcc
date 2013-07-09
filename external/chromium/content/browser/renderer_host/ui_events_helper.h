// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_UI_EVENTS_HELPER_H_
#define CONTENT_BROWSER_RENDERER_HOST_UI_EVENTS_HELPER_H_

#include "base/memory/scoped_vector.h"
#include "content/common/content_export.h"

namespace WebKit {
class WebGestureEvent;
class WebTouchEvent;
class WebTouchPoint;
}

namespace ui {
class GestureEvent;
class TouchEvent;
}

namespace content {

// Creates a list of ui::TouchEvents out of a single WebTouchEvent.
// A WebTouchEvent can contain information about a number of WebTouchPoints,
// whereas a ui::TouchEvent contains information about a single touch-point. So
// it is possible to create more than one ui::TouchEvents out of a single
// WebTouchEvent.
CONTENT_EXPORT bool MakeUITouchEventsFromWebTouchEvents(
    const WebKit::WebTouchEvent& touch,
    ScopedVector<ui::TouchEvent>* list);

// Creates a WebGestureEvent from a ui::GestureEvent. Note that it does not
// populate the event coordinates (i.e. |x|, |y|, |globalX|, and |globalY|). So
// the caller must populate these fields.
WebKit::WebGestureEvent MakeWebGestureEventFromUIEvent(
    const ui::GestureEvent& event);

int EventFlagsToWebEventModifiers(int flags);

// Updates the WebTouchEvent based on the TouchEvent. It returns the updated
// WebTouchPoint contained in the WebTouchEvent, or NULL if no point was
// updated.
WebKit::WebTouchPoint* UpdateWebTouchEventFromUIEvent(
    const ui::TouchEvent& event,
    WebKit::WebTouchEvent* web_event);
}

#endif  // CONTENT_BROWSER_RENDERER_HOST_UI_EVENTS_HELPER_H_