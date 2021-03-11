// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebBluetoothRemoteGATTService_h
#define WebBluetoothRemoteGATTService_h

#include "public/platform/WebString.h"

namespace blink {

struct WebBluetoothRemoteGATTService {
    WebBluetoothRemoteGATTService(const WebString& serviceInstanceID,
        const WebString& uuid,
        bool isPrimary,
        const WebString& deviceInstanceID)
        : serviceInstanceID(serviceInstanceID)
        , uuid(uuid)
        , isPrimary(isPrimary)
        , deviceInstanceID(deviceInstanceID)
    {
    }

    // Members corresponding to BluetoothRemoteGATTService attributes as
    // specified in the IDL.
    const WebString serviceInstanceID;
    const WebString uuid;
    const bool isPrimary;
    const WebString deviceInstanceID;
};

} // namespace blink

#endif // WebBluetoothRemoteGATTService_h
