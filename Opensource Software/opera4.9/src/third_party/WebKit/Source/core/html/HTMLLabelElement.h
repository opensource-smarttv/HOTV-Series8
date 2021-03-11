/*
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
 *           (C) 2000 Dirk Mueller (mueller@kde.org)
 * Copyright (C) 2004, 2005, 2006, 2007, 2010 Apple Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef HTMLLabelElement_h
#define HTMLLabelElement_h

#include "core/CoreExport.h"
#include "core/html/HTMLElement.h"

namespace blink {

class LabelableElement;

class CORE_EXPORT HTMLLabelElement final : public HTMLElement {
    DEFINE_WRAPPERTYPEINFO();
public:
    static HTMLLabelElement* create(Document&);
    LabelableElement* control() const;
    HTMLFormElement* form() const;

    bool willRespondToMouseClickEvents() override;

private:
    explicit HTMLLabelElement(Document&);
    bool isInInteractiveContent(Node*) const;

    bool isInteractiveContent() const override;
    void accessKeyAction(bool sendMouseEvents) override;

    InsertionNotificationRequest insertedInto(ContainerNode*) override;
    void removedFrom(ContainerNode*) override;

    // Overridden to update the hover/active state of the corresponding control.
    void setActive(bool = true) override;
    void setHovered(bool = true) override;

    // Overridden to either click() or focus() the corresponding control.
    void defaultEventHandler(Event*) override;

    void focus(const FocusParams&) override;

    bool m_processingClick;
};

} // namespace blink

#endif // HTMLLabelElement_h
